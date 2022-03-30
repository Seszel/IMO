#include "src/allinstances.hpp"
#include "src/allalgorithms.hpp"
#include "src/allsolutions.hpp"
#include "src/util_functions.hpp"

#include <iostream>

int main(int argc, char ** argv){

    srand(time(NULL));

    std::cout << getPathToWorkspaceFolder() << std::endl;

    InstanceTSP instance;

    auto path = getPathToWorkspaceFolder();
    path += "data/kroa100.tsp";
    instance.readFromFile(path);

    std::cout << "Data loaded" << std::endl;

    AlgorithmGreedyNN greedyNN;
    auto solution = greedyNN.run(instance);

    std::cout << solution.getTotalCost() << std::endl;

    AlgorithmBlindRunner blindRunner(&solution);

    auto blind_solution = blindRunner.run(instance);

    std::cout << blind_solution.getTotalCost() << std::endl;

    AlgorithmLocalGreedy algGreedy(&solution);

    auto greedySolution = algGreedy.run(instance);

    std::cout << greedySolution.getTotalCost() << std::endl;

    AlgorithmLocalSteepest localSteepest(&solution);

    auto steepSolution = localSteepest.run(instance);

    std::cout << steepSolution.getTotalCost() << std::endl;

    return 0;
}