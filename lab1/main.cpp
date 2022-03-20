#include "src/allinstances.hpp"
#include "src/allalgorithms.hpp"

#include <iostream>

int main(int argc, char ** argv){
    InstanceTSP instance;
    instance.readFromFile("../data/kroa100.tsp");

    std::cout << "Data loaded" << std::endl;

    AlgorithmGreedyNN greedyNN;
    auto solution = greedyNN.run(instance);

    std::cout << solution.getTotalCost() << std::endl;

    return 0;
}