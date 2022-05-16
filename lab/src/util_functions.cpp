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

    return std::hash<std::string>{}(std::to_string(move.a) + "_" + std::to_string(move.b) + "_" + std::to_string(move.type) + std::to_string(move.cyc_num));
}

const int isApplicable(Solution2Cycles & solution, Move move){
    return APPLICABLE;
    // check if the move is applicable
    bool b1 = (solution[move.cyc_num][move.a] == move.a_v);
    bool b2 = (solution[move.cyc_num][move.b] == move.b_v);

    if(b1 && b2){
        return NOT_APPLICABLE;
    }

    // check if move can be applied in the future
    b1 = (solution[move.cyc_num][move.a] == move.b_v);
    b2 = (solution[move.cyc_num][move.b] == move.a_v);

    if(!(b1 && b2)){
        //in the future
        return 2;
    }

    return APPLICABLE;
}