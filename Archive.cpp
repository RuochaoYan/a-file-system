#include "Archive.hpp"

Archive::Archive(std::string aName){
    dir = std::unique_ptr<Directory>(new Directory(aName));
}

Archive& Archive::add(std::string aFilename){
    std::fstream filetoAdd(aFilename,std::fstream::ate|std::fstream::binary);
    size_t fileSize=filetoAdd.tellg();
    std::vector<size_t> blocks = {1,2,3,4};
    dir->append(aFilename,fileSize,blocks);
    return *this;
}

/*Archive& Archive::add(std::string filename)
{
	//std::fstream file=
	return *this;
}*/
