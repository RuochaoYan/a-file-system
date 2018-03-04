#ifndef DIRECTORY_HPP_INCLUDED
#define DIRECTORY_HPP_INCLUDED
#include <vector>
#include <map>
#include <string>
    struct FileEntry{
        std::string filename;
        std::string filetype;
        size_t size;
        size_t firstblock;
    };

  class Directory{
  public:
    Directory(std::ofstream archive);
    Directory(std::ifstream archive);

  protected:
    std::map<std::string,FileEntry> files; //Maps name to the index of the corresponding FileEntry object
    std::vector<size_t> emptyblocks; // a vector of empty block indices
    size_t size; //size in blocks
  };

#endif // DIRECTORY_HPP_INCLUDED
