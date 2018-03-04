#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include <fstream>
#include <string>
#include <vector>

class Archive{
public:
    Archive(std::string name);
    //~Archive(): might not need it yet.
    Archive& add(std::string filename);
    Archive& del(std::string filename);
    Archive& list(std::string filename);
    Archive& listall();
    Archive& find(std::string filename);
    Archive& extract(std::string filename);

protected:
  struct Block{
    Block(size_t num, size_t next=0);
    size_t num = 0;
    size_t next = 0; //the number of the next block, 0 if no next block
    size_t size = 1024; // 1kByte blocks for now
  };

  class Directory{
  public:
    Directory(std::ofstream archive);
    Directory(std::ifstream archive);

  protected:
    class FileEntry{
        char filename[32];
        char filetype[3];
        size_t size;
        size_t firstblock;
    };

    std::vector<Block> files; //a vector of first blocks of the file
    std::vector<Block> emptyblocks; // a vector of empty blocks in the file
    size_t size; //size in blocks
  };
};
#endif // ARCHIVE_HPP_INCLUDED
