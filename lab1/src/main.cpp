#include "instanceTSP.hpp"
#include "algorithmCycleExpansion.hpp"
#include "solution2Cycles.hpp"

#include <iostream>

int main(int argc, char ** argv){
    InstanceTSP instance;
    instance.readFromFile("../data/kroa100.tsp");

    std::cout << "Data loaded" << std::endl;

    AlgorithmCycleExpansion alg;

    Solution2Cycles solution = alg.run(instance);

    std::cout << solution.getTotalCost() << std::endl;

    return 0;
}