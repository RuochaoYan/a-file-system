#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include <memory>
#include "Directory.hpp"

  struct Block{
    Block(size_t num);
    size_t num;
    size_t size = 1024; // 1kByte blocks for now
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
    std::unique_ptr<Directory> dir;
    std::vector<size_t> Blocks;
};
#endif // ARCHIVE_HPP_INCLUDED
