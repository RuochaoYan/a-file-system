#include "Archive.hpp"

Archive::Archive(std::string aName){
    dir = std::unique_ptr<Directory>(new Directory(aName));
}

Archive& Archive::add(std::string aFilename){
    std::vector<size_t> pizda = {1,2,3,4,5};
    dir->append(aFilename,3,pizda);
    return *this;
}
