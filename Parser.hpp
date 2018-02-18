#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED
#include <set>
#include <string>

class Parser {
public:
    Parser();
    //~Parser();

    void parse(int argc, char *argv[]); //I don't know what it should return yet

protected:
    std::set<std::string> commands;
};

#endif // PARSER_HPP_INCLUDED
