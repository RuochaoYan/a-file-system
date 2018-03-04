#include "Archive.hpp"

Archive::Archive(std::string aName){
    dir = std::unique_ptr<Directory>(new Directory(aName));
}

Archive& Archive::add(std::string aFilename){
    std::ifstream filetoAdd(aFilename,std::ifstream::ate|std::ifstream::binary);
    size_t fileSize=filetoAdd.tellg();
    dir->append(aFilename,fileSize,Blocks);
    return *this;
}

