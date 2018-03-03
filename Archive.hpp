#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include <vector>

class Block{
public:
    Block();
    size_t size() {return num_bytes;}
    size_t next = 0; //the number of the next block, 0 if no next block
protected:
    size_t num_bytes = 1024 // 1kByte blocks]
};

class FileEntry{
    char filename[32];
    char filetype[3];
    size_t size;
    size_t firstblock;
};

class Archive{
public:
    Archive(const char* name);
    //~Archive(): might not need it yet.
    add(const char* filename);
    del(const char* filename);
    list(const char* filename=nullptr);
    find(const char* filename);
    extract(const char* filename);

protected:
    std::vector<block> files;
    std::vector<block> emptyblocks;
    size_t size; //size in blocks
};
#endif // ARCHIVE_HPP_INCLUDED
