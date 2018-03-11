#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED
#include <set>
#include <string>
#include <iostream>
#include "Archive.hpp"
#include "Tester.hpp"
class Parser {
public:
    Parser();

    void parse(int argc, char *argv[]);

protected:
    std::set<std::string> commands;
};

#endif // PARSER_HPP_INCLUDED
