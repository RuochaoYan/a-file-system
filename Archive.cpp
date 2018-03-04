#include "Archive.hpp"

Archive::Archive(std::string name){
    dir = std::unique_ptr<Directory>(new Directory(name));
}
