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
    Archive(std::string name, bool newArc = 0);
    //~Archive(): might not need it yet.
    Archive& defrag();
    Archive& add(std::string filename);
    Archive& del(std::string filename);
    Archive& list(std::string filename);
    Archive& listall();
    Archive& find(std::string aString);
    Archive& findInOneFile(std::string aString, FileEntry aFile);
    Archive& extract(std::string filename);

protected:
    std::string arcname;
    std::unique_ptr<Directory> dir;
    std::vector<Block> Blocks;
    size_t lastBlockIndex; // indicating the largest index of blocks
};
#endif // ARCHIVE_HPP_INCLUDED
