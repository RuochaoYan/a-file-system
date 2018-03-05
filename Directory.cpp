#include "Directory.hpp"
#include "Archive.hpp"

FileEntry::FileEntry(){}

FileEntry::FileEntry(const std::string aFilename, const size_t aSize, const std::vector<Block> aBlocks){
    filename = aFilename;
    size = aSize;
    std::cout << "Blocks occupied: ";
    for(size_t i = 0; i<aBlocks.size(); ++i) {
        std::cout << aBlocks[i].num << " ";
        blocks.push_back(aBlocks[i].num);
    }
    std::cout << "" << std::endl;
    std::stringstream ss(aFilename);
    std::string s;
    int i = 0;
    while(getline(ss,s,'.')){
        if (i==2) filetype=s; // choose the part after the second "." cuz the first "." is for relative address
        i++;
    }
}

FileEntry::FileEntry(const std::string aLine){
    std::vector<std::string> words;
    std::string s;
    std::stringstream ss(aLine);
    while(getline(ss,s,' ')){
        words.push_back(s);
    }
    filename = words[0];
    filetype = words[1];
    size = std::stoll(words[2]);
    std::stringstream sss(words[3]);
    while(getline(sss,s,',')) blocks.push_back(std::stoll(s));
}


std::ostream& operator<<(std::ostream &os, const FileEntry& aF){
    os << aF.filename << ' ' << aF.filetype <<  ' '  << aF.size << ' ';
    for(size_t i = 0; i < aF.blocks.size(); ++i){
    if(i != 0) os << ",";
    os << aF.blocks[i];
}
    return os;
}

Directory::Directory(){}

Directory::Directory(const std::string aName):arcname(aName+".arc"){
    std::string s, s1;
    std::ifstream archive(arcname);
    if (archive.fail()){ //if the archive does not exist set default values
            std::cout << "No archive named "+ arcname + " yet\nCreating new archive" << std::endl;
        std::ofstream newArchive(arcname); // create a new archive
            files = {};
            emptyblocks = {};
            size = 1; //at least the first block is already occupied
            lastBlock = 0; // the first block
    }
    else{ //if the archive already exists
        int i = 0;
        while(getline(archive,s)){
            if (i==0){
                size=std::stoll(s);
                i++;
                lastBlock = std::max(lastBlock, size-1);
            } //first line: size of directory in blocks
            else if (i==1){ //second line: vector of empty blocks
                std::stringstream ss(s);
                while(getline(ss,s1,',')) emptyblocks.push(std::stoll(s1));
                i++;
            }
            else if("EOF"==s) break;
            else{
                FileEntry f = FileEntry(s);
                files[f.filename] = f;
                for(size_t i : f.blocks){
                    lastBlock = std::max(lastBlock, i); // achieve the maximal index of blocks
                }
            }
        }
    }
}

Directory& Directory::append(const std::string aFilename, const size_t aSize, const std::vector<Block> aBlocks){
    FileEntry f = FileEntry(aFilename,aSize,aBlocks);
    files[f.filename] = f;
    return *this;
}

Directory& Directory::extractFile(const std::string filename)
{
    std::string content;
    FileEntry f=files[filename];
    std::ifstream filetoPrint(f.filename);
    while(getline(filetoPrint,content))
    {
       std::cout<<content<<std::endl;
   }
 return *this;
}

size_t Directory::getAnEmptyBlock(){
    size_t res = emptyblocks.front();
    emptyblocks.pop();
    return res;
}

void Directory::deleteAFile(std::string filename){
    FileEntry f=getFileEntry(filename);
    for(size_t block : f.blocks){ // add this file's blocks to emptyblocks
        addAnEmptyBlock(block);
    }
    files.erase(filename);
}

void Directory::listAllFiles(){
    for (std::map<std::string,FileEntry>::iterator it=files.begin(); it!=files.end(); ++it){
        std::cout << it->first << " " << it->second.size << "Bytes" << std::endl;
    }
}

void Directory::listOneFile(std::string aFilename){
    std::cout << aFilename << " " << files[aFilename].size << "Bytes" << std::endl;
}

std::ostream& operator<<(std::ostream &os,Directory& aDir){
    std::string s, s1;
    os << aDir.size << '\n';
    for(size_t i = 0; !aDir.emptyblocks.empty(); ++i){
    if(i != 0) os << ",";
        os << aDir.emptyblocks.front();
        aDir.emptyblocks.pop();
    }
    os << '\n';
    for (std::map<std::string,FileEntry>::iterator it=aDir.files.begin(); it!=aDir.files.end(); ++it){
        os << it->second << '\n';
    }
    os << "EOF" << std::endl;
    return os;
}

