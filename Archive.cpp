#include "Archive.hpp"

Archive::Archive(std::string aName): arcname(aName+".arc"){
    dir = std::unique_ptr<Directory>(new Directory(aName));
    for(size_t i = 0; i<(dir->getSize()); ++i){
        Blocks.push_back(i); // i feel that the Blocks vector is not necessary here in Archive.cpp, cuz we only need to record how many blocks in total the archive occupies. the detail thing of blocks are aready stored in Directory and fileEntry.
    }
    lastBlockIndex = dir->lastBlock;
}

Archive& Archive::add(std::string aFilename){
    /*
     need to consider filename conflict
     */
    std::vector<Block> blocks; //vector of block number
    std::ifstream filetoAdd(aFilename,std::ifstream::ate|std::ifstream::binary);
    size_t fileSize=filetoAdd.tellg();
    size_t blocknum = fileSize/1024 + 1; //number of blocks needed
    std::cout << "Filesize:" << fileSize <<  "\nNumber of Blocks: " << blocknum << std::endl;
    for(size_t i=1; i<=blocknum; ++i) {
        if(dir->hasEmptyBlocks()){ // add to the empty blocks
            blocks.push_back(Block(dir->getAnEmptyBlock()));
        }
        else{ // append to the end of the archive
            lastBlockIndex++;
            blocks.push_back(Block(lastBlockIndex));
        }
        //blocks.push_back(Block(i)); //trivially choosing successive blocks SHOULD BE MORE INTELLIGENT!!!
    }
    std::cout << "First Block:" << blocks[0].num << std::endl;
    dir->append(aFilename,fileSize,blocks); //passing blocks to dir
    
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
    // how to mark the end of the file?
    return *this;
}

Archive& Archive::del(std::string filename){
    // we don't really delete contents in those blocks. we just mark them as illegal (emptyblocks)
    // but the remaining contents might disturb when we reuse the block with shorter length of contents
    // so we need to make a mark at the end of every file?
    dir->deleteAFile(filename);
    std::fstream archivefile(arcname,std::fstream::binary | std::fstream::out | std::fstream::in); // use fstream with "in" to avoid deleting the original contents
    archivefile << *dir;
    return *this;
}

Archive& Archive::listall(){
    dir->listAllFiles();
    return *this;
}

Archive& Archive::list(std::string filename){
    // we should add a date-added property to files first
    return *this;
}

Archive& Archive::find(std::string aString){
    // show properties of any textfile that contain the given string
    return *this;
}

Archive& Archive::extract(std::string filename)
{
    std::string content;
    // should handle file not found
    FileEntry f=dir->getFileEntry(filename);
    std::ifstream archive(arcname, std::ifstream::binary);
    for(size_t blockIndex : f.blocks){ // for every block of this file
        Block block(blockIndex);
        archive.seekg(block.startPos()); // move the file pointer to the beigining of this block
        if(f.filetype == "txt"){ // it is a text file
            std::string s;
            while(getline(archive,s)){
                std::cout << s << std::endl;
            }
            // how to handle it when the file pointer reached the end of the block?
        }
        else{ // it is a binary file
            int i = 0;
            while(archive.good() && i < 1024){ // print the contents in this block
                std::cout << archive.get() << std::endl;
                i++;
            }
        }
    }
	return *this;
}
