#include "Directory.hpp"

FileEntry::FileEntry(){}

FileEntry::FileEntry(const std::string aFilename, const size_t aSize, const std::vector<size_t> aBlocks){
    filename = aFilename;
    size = aSize;
    blocks = aBlocks;
    std::stringstream ss(aFilename);
    std::string s;
    int i = 0;
    while(getline(ss,s,',')){
        if (i==1) filetype=s;
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
    size = std::stoi(words[2]);
    std::stringstream sss(words[3]);
    while(getline(sss,s,',')) blocks.push_back(std::stoi(s));
}


std::ostream& operator<<(std::ostream &os, const FileEntry& aF){
    os << aF.filename << ' ' << aF.filetype <<  ' '  << aF.size << ' ';
    for(size_t i = 0; i < aF.blocks.size(); ++i){
    if(i != 0) os << ",";
    os << aF.blocks[i];
}
    return os;
}

Directory::Directory(const std::string aName):arcname(aName){
    std::string s, s1;
    std::ifstream archive(arcname);
    if (archive.fail()){ //if the archive does not exist set default values
            std::cout << "No archive named "+ arcname + " yet\nCreating new archive" << std::endl;
            files = {};
            emptyblocks = {};
            size = 1; //at least the first block is already occupied
    }
    else{ //if the archive already exists
        int i = 0;
        while(getline(archive,s)){
            if (i==0){size=std::stoi(s); i++;}
            if (i==1){
                std::stringstream ss(s);
                while(getline(ss,s1,',')) emptyblocks.push_back(std::stoi(s1));
            }
            else{
                FileEntry f = FileEntry(s);
                files[f.filename] = f;
            }
        }
    }
}

Directory::~Directory(){
    std::string s, s1;
    std::ofstream archive(arcname);
    archive << size << std::endl;
    for(size_t i = 0; i < emptyblocks.size(); ++i){
    if(i != 0) archive << ",";
    archive << emptyblocks[i];
    }
    archive << std::endl;
    for (std::map<std::string,FileEntry>::iterator it=files.begin(); it!=files.end(); ++it){
        archive << it->second << std::endl;
    }
}

Directory& Directory::append(const std::string aFilename, const size_t aSize, const std::vector<size_t> aBlocks){
    FileEntry f = FileEntry(aFilename,aSize,aBlocks);
    files[f.filename] = f;
    return *this;
}

