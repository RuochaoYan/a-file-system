#include "Parser.hpp"

Parser::Parser(){
    commands = {"add","del","list","-l","find","extract","version","-v"};
}

void Parser::parse(int argc, char *argv[]){
    if (argc > 1){
        if (commands.find(argv[1]) == commands.end()) {
            std::cout << "Sorry, the command that you input is invalid\n";
        }
        else {
            std::string command = std::string(argv[1]);
            if ("version"==command || "-v"==command) std::cout << "sfarchiver version 0.2 February 21, 2018\n";
        }
    }
}
