#include "src/allinstances.hpp"
#include "src/allalgorithms.hpp"
#include "src/allsolutions.hpp"

#include <iostream>

int main(int argc, char ** argv){
    InstanceTSP instance;
    instance.readFromFile("/home/piotr/Dokumenty/SI/imo/IMO/lab1/data/kroa100.tsp");

    std::cout << "Data loaded" << std::endl;

    AlgorithmGreedyNN greedyNN;
    auto solution = greedyNN.run(instance);

    // AlgorithmBlindRunner blindRunner(&solution);

    // auto blind_solution = blindRunner.run(instance);

    // std::cout << blind_solution.getTotalCost() << std::endl;

    return 0;
}