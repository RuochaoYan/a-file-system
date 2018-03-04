#ifndef DIRECTORY_HPP_INCLUDED
#define DIRECTORY_HPP_INCLUDED
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

    struct FileEntry{
        std::string filename;
        std::string filetype;
        size_t size;
        size_t firstblock;
    };

  class Directory{
  public:
    Directory(std::string name);

  protected:
    std::map<std::string,FileEntry> files; //Maps filename to the corresponding FileEntry object
    std::vector<size_t> emptyblocks; // a vector of empty block indices
    size_t size; //size in blocks
  };

#endif // DIRECTORY_HPP_INCLUDED
