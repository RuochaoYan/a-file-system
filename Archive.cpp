#include "Archive.hpp"
#include <cstring>
#include <unistd.h>
#include <sys/types.h>

       int truncate(const char *path, off_t length);
       int ftruncate(int fd, off_t length);

// discard the address, only maintain the name of the file e.g. "./testfiles/test1.txt" -> "test1.txt"
std::string parseFilename(std::string aFileAddress){
    std::stringstream ss(aFileAddress);
    std::string s;
    while(getline(ss,s,'/')){
    }
    return s;
}

Archive::Archive(std::string aName, bool newArc): arcname(aName+".arc"){
    dir = std::unique_ptr<Directory>(new Directory(aName,newArc));
    for(size_t i = 0; i<(dir->getSize()); ++i){
        Blocks.push_back(i); // i feel that the Blocks vector is not necessary here in Archive.cpp, cuz we only need to record how many blocks in total the archive occupies. the detail thing of blocks are aready stored in Directory and fileEntry.
    }
    lastBlockIndex = dir->lastBlock;
}

Archive& Archive::defrag(){
    std::ifstream is(arcname);
    std::fstream os(arcname,std::fstream::binary | std::fstream::out | std::fstream::in);
    size_t goalSize = (dir->lastBlock + 1 - dir->numEmptyBlocks());
    while(dir->hasEmptyBlocks()){
        Block curBlock = Block(dir->getAnEmptyBlock());
        if (curBlock.num >= goalSize) continue;
            for(std::map<std::string,FileEntry>::iterator it=dir->getFileBegin(); it!=dir->getFileEnd(); ++it)
            for(size_t i = 0; i < it->second.blocks.size(); ++i) {
                if (goalSize <= it->second.blocks[i]) {
                    is.seekg((it->second.blocks[i])*1024);
                    os.seekp((curBlock.num)*1024);
                    for(size_t i=0;i<1024;i++)  os.put(is.get());
                    it->second.blocks[i] = curBlock.num;
                    goto exit;
                }
            }
        exit:
        []{}; //no op
    }
    os.seekp(0);
    os << *dir;
    truncate(arcname.c_str(),goalSize);
    return *this;
}

Archive& Archive::add(std::string aFileAddress){
    std::cout << ("Adding file at " + aFileAddress + " to " + arcname) << std::endl;
    std::string theFilename = parseFilename(aFileAddress);

    // consider filename conflict
    if(dir->contains(theFilename)){
        std::cout << "Failed to add the file. A file with the same name already exists." << std::endl;
        return *this;
    }

    std::vector<Block> blocks; //vector of block number
    std::ifstream filetoAdd(aFileAddress,std::ifstream::ate|std::ifstream::binary);
    size_t fileSize=filetoAdd.tellg();
    size_t blocknum = fileSize/1024 + 1; //number of blocks needed
    std::cout << "Filesize:" << fileSize <<  "\nNumber of Blocks: " << blocknum << std::endl;
    for(size_t i=1; i<=blocknum; ++i) {
        if(dir->hasEmptyBlocks()){ // add to the empty blocks
            blocks.push_back(Block(dir->getAnEmptyBlock()));
        }
        else{ // append to the end of the archive
            lastBlockIndex++;
            Block lastBlock(lastBlockIndex);
            blocks.push_back(lastBlock);
        }
    }
    std::cout << "First Block:" << blocks[0].num << std::endl;
    dir->append(theFilename,fileSize,blocks); //passing blocks to dir

    std::fstream archivefile(arcname,std::fstream::binary | std::fstream::out | std::fstream::in); // use fstream with "in" to avoid deleting the original contents

    std::cout << "Startpos: " << blocks[0].startPos() << std::endl;
    archivefile << *dir;

    filetoAdd.seekg(0, std::ios::beg); // move the pointer back to the beginning
    for(Block block : blocks){
        archivefile.seekp(block.startPos());
        int i = 0;
        while(filetoAdd.peek() != EOF && i < 1024)
        {
            archivefile.put(filetoAdd.get());
            i++;
        }
    }
    std::cout << "Successfully added!" << std::endl;
    return *this;
}

Archive& Archive::del(std::string aFilename){
    std::string theFilename = parseFilename(aFilename);
    dir->deleteAFile(theFilename);
    std::fstream archivefile(arcname,std::fstream::binary | std::fstream::out | std::fstream::in); // use fstream with "in" to avoid deleting the original contents
    archivefile << *dir;
    std::cout << "Successfully deleted!" << std::endl;
    return *this;
}

Archive& Archive::listall(){
    dir->listAllFiles();
    return *this;
}

Archive& Archive::list(std::string aFilename){
    std::string theFilename = parseFilename(aFilename);
    // we should add a date-added property to files first
    if(dir->contains(theFilename)){
        dir->listOneFile(theFilename);
    }
    else
        std::cout << "File not found" << std::endl;
    return *this;
}

Archive& Archive::find(std::string aString){
    // show properties of any textfile that contain the given string
    std::vector<FileEntry> textFiles = dir->getAllTextFiles();
    aString.substr(1, aString.size()-2);
    for(FileEntry f : textFiles){
        findInOneFile(aString, f);
    }
    return *this;
}

// find if aString exists in aFile
Archive& Archive::findInOneFile(std::string aString, FileEntry aFile){
    std::ifstream archive(arcname, std::ifstream::binary);
    size_t fileSize = 0;
    std::string temp(aString.size(), ' ');
    for(size_t blockIndex : aFile.blocks){ // for every block of this file
        Block block(blockIndex);
        archive.seekg(block.startPos()); // move the file pointer to the beigining of this block
        char x[1];
        int i = 0;
        while(archive.peek() != EOF && fileSize < aFile.size && i < 1024){
            archive.read(x,1);
            temp.erase(0, 1);
            temp.push_back(x[0]);
            if(temp == aString){
                dir->listOneFile(aFile.filename);
                return *this;
            }
            i++;
            fileSize++;
        }
    }
    return *this;
}

Archive& Archive::extract(std::string aFilename)
{
    std::string theFilename = parseFilename(aFilename);
    // handle file not found
    if(!dir->contains(theFilename)){
        std::cout << "File not found." << std::endl;
        return *this;
    }

    std::string content;
    FileEntry f=dir->getFileEntry(theFilename);
    std::ifstream archive(arcname, std::ifstream::binary);
    size_t fileSize = 0;
    for(size_t i = 0; i < f.blocks.size(); i++){ // for every block of this file
        Block block(f.blocks[i]);
        archive.seekg(block.startPos(), std::ios::beg); // move the file pointer to the beigining of this block
        if(f.filetype == "txt"){ // it is a text file
            if(i == Blocks.size()-1){
                const size_t blockSize = f.size % 1024;
                char* x = new char[blockSize+1];
                memset(x, 0, blockSize+1);
                archive.read(x,blockSize);
                std::cout << x;
                delete[] x;
            }
            else{
                char* x = new char[1025];
                memset(x, 0, 1025);
                archive.read(x,1024);
                std::cout << x;
                delete[] x;
            }
        }
        else{ // for printing the binary code in binary files
            int i = 0;
            while(archive.peek() != EOF && i < 1024 && fileSize < f.size){ // print the contents in this block
                int num = archive.get();
                if(num < 16)
                    std::cout << "0";
                std::cout << std::hex << num ;
                i++;
               fileSize++;
                if(i % 2 == 0) std::cout << " " ;
            }
        }
    }
    std::cout << "" << std::endl;
	return *this;
}
