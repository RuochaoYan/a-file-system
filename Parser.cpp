#include "Parser.hpp"
#include <iostream>

Parser::Parser(){
    commands = {"add","del","list","-l","find","extract","version","-v"};
}

void Parser::parse(int argc, char *argv[]){
    if (argc > 1){
        if (commands.find(argv[1]) == commands.end()) {
            std::cout << "Sorry, the command that you input is invalid\n";
        }
    }
}
