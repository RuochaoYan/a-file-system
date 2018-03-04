#include "Archive.hpp"

Archive::Archive(std::string aName){
    dir = std::unique_ptr<Directory>(new Directory(aName));
}

Archive& Archive::add(std::string aFilename){
    std::vector<size_t> blocks; //vector of block number
    std::ifstream filetoAdd(aFilename,std::ifstream::ate|std::ifstream::binary);
    size_t fileSize=filetoAdd.tellg();
    size_t blocknum = fileSize/1024 + 1; //number of blocks needed
    std::cout << "Filesize:" << fileSize <<  "\nNumber of Blocks: " << blocknum << std::endl;
    for(size_t i=1; i<=blocknum; ++i) blocks.push_back(i); //trivially choosing successive blocks SHOULD BE MORE INTELLIGENT!!!
    std::cout << "First Block:" << blocks[0] << std::endl;
    dir->append(aFilename,fileSize,blocks); //passing blocks to dir
    return *this;
}



Archive& Archive::extract(std::string filename)
{
	 dir->extractFile(filename);

	return *this;

}
