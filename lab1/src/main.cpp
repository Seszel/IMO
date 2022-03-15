#include "instanceTSP.hpp"
#include "algorithmCycleExpansion.hpp"
#include "solution2Cycles.hpp"
#include "algorithm2regret.hpp"

#include <iostream>
#include <cstdlib>
#include <cstdio>

int main(int argc, char ** argv){

    srand(time(NULL));

    InstanceTSP instance;
    instance.readFromFile("../data/kroa100.tsp");

    std::cout << "Data loaded" << std::endl;

    AlgorithmCycleExpansion alg;

    Solution2Cycles solution2cycles = alg.run(instance);

    std::cout << solution2cycles.getTotalCost() << std::endl;

    Algorithm2Regret alg2regret;

    Solution2Cycles solutionRegret = alg.run(instance);

    std::cout <<solutionRegret.getTotalCost() << std::endl;

    return 0;
}