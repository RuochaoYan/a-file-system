#include "Archive.hpp"

// discard the address, only maintain the name of the file e.g. "./testfiles/test1.txt" -> "test1.txt"
std::string parseFilename(std::string aFileAddress){
    std::stringstream ss(aFileAddress);
    std::string s;
    while(getline(ss,s,'/')){
    }
    return s;
}

Archive::Archive(std::string aName): arcname(aName+".arc"){
    dir = std::unique_ptr<Directory>(new Directory(aName));
    for(size_t i = 0; i<(dir->getSize()); ++i){
        Blocks.push_back(i); // i feel that the Blocks vector is not necessary here in Archive.cpp, cuz we only need to record how many blocks in total the archive occupies. the detail thing of blocks are aready stored in Directory and fileEntry.
    }
    lastBlockIndex = dir->lastBlock;
}

Archive& Archive::add(std::string aFileAddress){
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
    archivefile.seekp(blocks[0].startPos());
    filetoAdd.clear();
    filetoAdd.seekg(0); // move the pointer back to the beginning
    while(filetoAdd.good())
    {
    	archivefile.put(filetoAdd.get());
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
    for(size_t blockIndex : f.blocks){ // for every block of this file
        Block block(blockIndex);
        archive.seekg(block.startPos()); // move the file pointer to the beigining of this block
        if(f.filetype == "txt"){ // it is a text file
            char x[1];
            int i = 0;
            while(archive.peek() != EOF && archive.peek() != 0xff && i < 1024) // 0xff is the EOF we stored in the archive
            {
                archive.read(x,1);
                std::cout << x;
                i ++;
            }
        }
        else{ // it is a binary file
            int i = 0;
            while(archive.peek() != EOF && archive.peek() != 0xff && i < 1024){ // print the contents in this block
                std::cout << archive.get() ;
                i++;
            }
        }
        std::cout << "" << std::endl;
    }
	return *this;
}
