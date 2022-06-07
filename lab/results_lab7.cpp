#include "src/allalgorithms.hpp"
#include "src/allinstances.hpp"
#include "src/allsolutions.hpp"
#include "lib/json/single_include/nlohmann/json.hpp"
#include "src/util_functions.hpp"

#include <chrono>
#include <unistd.h>

#include <ctime>
#include <omp.h>
#include <mutex>
#include <thread>

#include <iostream>
#include <fstream>

using namespace nlohmann;

int main(){

    srand(time(NULL));

    Solution2Cycles solution;

    std::fstream file;

    auto path = getPathToWorkspaceFolder();

    // auto t = std::chrono::system_clock::now();
    // std::time_t timestamp = std::chrono::system_clock::to_time_t(t);

    // file.open(path + "resultFiles/" + std::string(std::ctime(&timestamp)) + ".json", std::ios::out);


    //load instances
    auto pathA = getPathToWorkspaceFolder();
    pathA += "data/kroa200.tsp";
    auto pathB = getPathToWorkspaceFolder();
    pathB += "data/krob200.tsp";

    InstanceTSP A, B;
    A.readFromFile(pathA);
    B.readFromFile(pathB);
    std::cout << "Data loaded." << std::endl;

    auto myalg = MyAlgorithm(nullptr);
    auto cyc_exp = AlgorithmCycleExpansion();
    auto sol = cyc_exp.run(A);
    myalg.setStartingSolution(&sol);
    sol = myalg.run(A);

    std::cerr << sol.getTotalCost() << std::endl;

    return 0;
}