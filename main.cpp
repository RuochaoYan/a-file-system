#include "Parser.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    Parser theParser = Parser();
    theParser.parse(argc,argv);
}
