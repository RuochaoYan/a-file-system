#ifndef DIRECTORY_HPP_INCLUDED
#define DIRECTORY_HPP_INCLUDED
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

struct Block;

    struct FileEntry{
        std::string filename;
        std::string filetype;

        size_t size;
        std::vector<size_t> blocks;

        FileEntry();
        FileEntry(const std::string aFilename, const size_t aSize, const std::vector<Block> aBlocks);
        FileEntry(const std::string aLine);

    };

    std::ostream& operator<<(std::ostream &os,const FileEntry& aF);

  class Directory{
  public:
    Directory();
    Directory(const std::string aName);
    void writeDir();

    Directory& extractFile(const std::string filename);

    Directory& append(const std::string aFilename, const size_t aSize, const std::vector<Block> aBlocks);

    size_t getSize(){return size;}
    FileEntry getFileEntry(std::string filename){return files[filename];}
    
      bool hasEmptyBlocks(){return !emptyblocks.empty();}
      size_t getAnEmptyBlock();
      void addAnEmptyBlock(size_t aBlock){emptyblocks.push(aBlock);}
      void deleteAFile(std::string filename);
      void listAllFiles();
      
    friend std::ostream& operator<<(std::ostream &os,Directory& aDir);
      size_t lastBlock; // the maximal index of blocks in the archive

  protected:
    std::string arcname;
    std::map<std::string,FileEntry> files; //Maps filename to the corresponding FileEntry object
    std::queue<size_t> emptyblocks; // a vector of empty block indices
    size_t size; //size in blocks
    
  };

#endif // DIRECTORY_HPP_INCLUDED
