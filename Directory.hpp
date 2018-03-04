#ifndef DIRECTORY_HPP_INCLUDED
#define DIRECTORY_HPP_INCLUDED
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

    struct FileEntry{
        std::string filename;
        std::string filetype;
        
        size_t size;
        std::vector<size_t> blocks;

        FileEntry();
        FileEntry(const std::string aFilename, const size_t aSize, const std::vector<size_t> aBlocks);
        FileEntry(const std::string aLine);

    };

    std::ostream& operator<<(std::ostream &os,const FileEntry& aF);

  class Directory{
  public:
    Directory(const std::string aName);
    ~Directory();

    Directory& extractFile(const std::string filename);

    Directory& append(const std::string aFilename, const size_t aSize, const std::vector<size_t> aBlocks);

  protected:
    std::string arcname;
    std::map<std::string,FileEntry> files; //Maps filename to the corresponding FileEntry object
    std::vector<size_t> emptyblocks; // a vector of empty block indices
    size_t size; //size in blocks
  };

#endif // DIRECTORY_HPP_INCLUDED
