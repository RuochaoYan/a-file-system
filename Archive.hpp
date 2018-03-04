#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include <memory>
#include "Directory.hpp"

  struct Block{
    Block(size_t num): num(num) {}
    size_t num;
    size_t size = 1024; // 1kByte blocks for now

    size_t startPos() {return num*size;} //returns the position where the file needs to be written
    size_t endPos() {return startPos() + size;}
  };

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
    std::string arcname;
    std::unique_ptr<Directory> dir;
    std::vector<Block> Blocks;
};
#endif // ARCHIVE_HPP_INCLUDED
