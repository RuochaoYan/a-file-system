#include "Directory.hpp"
#include "Archive.hpp"

FileEntry::FileEntry(){}

FileEntry::FileEntry(const std::string aFilename, const size_t aSize, const std::vector<Block> aBlocks){
    filename = aFilename;
    size = aSize;
    for(size_t i = 0; i<aBlocks.size(); ++i) {std::cout << aBlocks[i].num << std::endl; blocks.push_back(aBlocks[i].num);}
    std::stringstream ss(aFilename);
    std::string s;
    int i = 0;
    while(getline(ss,s,'.')){
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
            files = {};
            emptyblocks = {};
            size = 1; //at least the first block is already occupied
    }
    else{ //if the archive already exists
        int i = 0;
        while(getline(archive,s)){
            if (i==0){size=std::stoll(s); i++;} //first line: size of directory in blocks
            else if (i==1){ //second line: vector of empty blocks
                std::stringstream ss(s);
                while(getline(ss,s1,',')) emptyblocks.push_back(std::stoll(s1));
                i++;
            }
            else if("EOF"==s) break;
            else{
                FileEntry f = FileEntry(s);
                files[f.filename] = f;
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

std::ostream& operator<<(std::ostream &os,Directory& aDir){
    std::string s, s1;
    os << aDir.size << '\n';
    for(size_t i = 0; i < aDir.emptyblocks.size(); ++i){
    if(i != 0) os << ",";
    os << aDir.emptyblocks[i];
    }
    os << '\n';
    for (std::map<std::string,FileEntry>::iterator it=aDir.files.begin(); it!=aDir.files.end(); ++it){
        os << it->second << '\n';
    }
    os << "EOF" << std::endl;
    return os;
}

