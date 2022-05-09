#include "util_functions.hpp"

const std::string getPathToWorkspaceFolder(){

    char pathName[FILENAME_MAX];
    getcwd(pathName, FILENAME_MAX);

    std::string directory(pathName);
    directory += "/";

    auto pos = directory.rfind("/lab/");
    if(pos == std::string::npos){
        std::cerr << "cannot find directory" << std::endl;
        return "";
    }

    directory = directory.substr(0, pos + 1);
    directory += "lab/";
    return directory;

}

const std::size_t getHashOfMove(Move move){

    return std::hash<std::string>{}(std::to_string(move.a_v) + "_" + std::to_string(move.b_v));
}

const int isApplicable(Solution2Cycles & solution, Move move){

    
}