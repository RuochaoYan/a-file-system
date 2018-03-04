#include "Archive.hpp"

Archive::Archive(std::string name){
    std::ifstream archive(name);
    if (archive.fail()){
        std::ofstream archive(name);
    }
}
