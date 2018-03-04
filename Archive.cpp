#include "Archive.hpp"

Archive::Archive(std::string aName): arcname(aName+".arc"){
    dir = std::unique_ptr<Directory>(new Directory(aName));
    for(size_t i = 0; i<(dir->getSize()); ++i){
        Blocks.push_back(i);
    }
}

Archive& Archive::add(std::string aFilename){
    std::vector<Block> blocks; //vector of block number
    std::ifstream filetoAdd(aFilename,std::ifstream::ate|std::ifstream::binary);
    size_t fileSize=filetoAdd.tellg();
    size_t blocknum = fileSize/1024 + 1; //number of blocks needed
    std::cout << "Filesize:" << fileSize <<  "\nNumber of Blocks: " << blocknum << std::endl;
    for(size_t i=1; i<=blocknum; ++i) blocks.push_back(Block(i)); //trivially choosing successive blocks SHOULD BE MORE INTELLIGENT!!!
    std::cout << "First Block:" << blocks[0].num << std::endl;
    dir->append(aFilename,fileSize,blocks); //passing blocks to dir

    std::ofstream archivefile(arcname/*,std::ios::binary*/);
    std::cout << "Startpos: " << blocks[0].startPos() << std::endl;
    archivefile << *dir;
    archivefile.seekp(blocks[0].startPos());
    while(filetoAdd.good())
    {
    	archivefile.put(filetoAdd.get());
    }
    return *this;
}



Archive& Archive::extract(std::string filename)
{
    std::string content;
	FileEntry f=dir->getFileEntry(filename);
	std::ifstream filetoPrint(f.filename);
	while(getline(filetoPrint,content))
	{
		std::cout<<content<<std::endl;
	}

	return *this;

}
