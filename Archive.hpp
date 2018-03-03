#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include <vector>

class block{
public:
    size_t blockSize() {return num_bytes;}
    size_t next = 0; //the number of the next block, 0 if no next block
protected:
    size_t num_bytes = 1024 // 1kByte blocks]
};

class file_entry{
    char filename[32];
    char filetype[3];
    size_t size;
    size_t firstblock;
};

class repo{
    std::vector<block> files;
    size_t size; //size in blocks
    std::vector<block> emptyblocks;
};
#endif // ARCHIVE_HPP_INCLUDED
