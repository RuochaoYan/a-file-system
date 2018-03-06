#include "Parser.hpp"

Parser::Parser(){
    commands = {"add","del","list","-l","find","extract","version","-v"};
}

void Parser::parse(int argc, char *argv[]){
    if (argc == 1){
            std::cout << "Welcome to SFArchiver by the Team It Compiles!\n\n" <<
            "List of command:\n" <<
            "sfarchiver: help file\n" <<
            "sfarchiver add [ARCHIVE_NAME] [FILE_NAME]: add [FILE_NAME] to the [ARCHIVE_NAME]\n" <<
            "sfarchiver del [ARCHIVE_NAME] [FILE_NAME]: delete [FILE_NAME] from the [ARCHIVE_NAME]\n" <<
            "sfarchiver list (-l) [ARCHIVE_NAME]: list all files in the [ARCHIVE_NAME]\n" <<
            "sfarchiver list (-l) [ARCHIVE_NAME] [FILE_NAME]: show detailed properties of the [FILE_NAME] in the [ARCHIVE_NAME]\n" <<
            "sfarchiver find [ARCHIVE_NAME] [STRING]: show detailed propertied of the file containing [STRING] in the [ARCHIVE_NAME]\n" <<
            "sfarchiver extract [ARCHIVE_NAME] [FILE_NAME]: extract [FILE_NAME] from the [ARCHIVE_NAME]\n" <<
            "sfarchiver version (-v): Display the version of sfarchiver" << std::endl;
    }
    else{
        std::string command = std::string(argv[1]);
        if (commands.find(command) == commands.end()) std::cerr << "Sorry, the command that you input is invalid.\nPlease, run \"sfarchiver\" for the list of commands." << std::endl;
        else if ("version"==command || "-v"==command) std::cout << "sfarchiver version 0.3 March 3, 2018" << std::endl;
        else if ((argc==3 && ("list"==command || "-l" == command))  || argc==4){
                Archive arc = Archive(std::string(argv[2]));
                if("add"==command) arc.add(std::string(argv[3]));
                else if("del"==command){
                    std::string fileDelete=std::string(argv[3]);
                    arc.del(fileDelete);
                }
                else if(argc == 3 && ("list"==command || "-l" == command)){
                    arc.listall();
                }
                else if(argc == 4 && ("list"==command || "-l" == command)){
                    std::string fileList = std::string(argv[3]);
                    arc.list(fileList);
                }
                else if("extract"==command)
                {
                    std::string fileExtract=std::string(argv[3]);
                    arc.extract(fileExtract);
                }
                //else if("del"==command && argc==4) arc.del(argv[3]);
                //else if(("list"==command || "-l"==command) && argc==3) arc.listall();
            }
        else std::cerr << "Sorry, the arguments that you input are invalid.\nPlease, run \"sfarchiver\" for help." << std::endl;
    }
}
