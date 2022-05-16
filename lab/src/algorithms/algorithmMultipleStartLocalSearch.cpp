#include "algorithmMultipleStartLocalSearch.hpp"

const Solution2Cycles AlgorithmMultipleStartLocalSearch::run(const InstanceTSP & instance){


    Solution2Cycles bestSolution, currentSolution;

    int cost = RAND_MAX;
    AlgorithmRandom alg_random = AlgorithmRandom();
    AlgorithmLocalSteepest alg_local = AlgorithmLocalSteepest(nullptr);

    for(int i = 0; i < this->ITERATIONS; i ++){

        //generate starting solution
        currentSolution = alg_random.run(instance);

        //apply local search
        alg_local.setStartingSolution(&currentSolution);
        currentSolution = alg_local.run(instance);

        if(currentSolution.getTotalCost() < cost){
            cost = currentSolution.getTotalCost();
            bestSolution = currentSolution;
        }
    }

    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void AlgorithmMultipleStartLocalSearch::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmMultipleStartLocalSearch::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}