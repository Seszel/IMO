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

    AlgorithmCycleExpansion cycleExpansion;
    auto solution = cycleExpansion.run(instance);
    std::cout << solution.getTotalCost() << std::endl;

    AlgorithmLocalCandidates localCandidates(&solution);
    auto candidatesSolution = localCandidates.run(instance);
    std::cout << candidatesSolution.getTotalCost() << std::endl;

    return 0;
}