#include "algorithmCycleExpansion.hpp"

const Solution2Cycles AlgorithmCycleExpansion::run(const InstanceTSP & instance){

    Solution2Cycles finalSolution;

    //choose random startin vertex
    int randomStart = rand() % instance.dimension;

    //find closest neighbor

}