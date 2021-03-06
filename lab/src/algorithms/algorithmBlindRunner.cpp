#include "algorithmBlindRunner.hpp"

const Solution2Cycles AlgorithmBlindRunner::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    int duration = 0;

    auto start = std::chrono::steady_clock::now();

    while(duration < 500){

        int op = rand()% availableMoveTypes.size();

        if(availableMoveTypes[op] == Solution2Cycles::SWAP_BETWEEN_CYCLES){

            const int a = rand() % currentSolution[0].getLength();
            const int b = rand() % currentSolution[1].getLength();

            currentSolution.swapVerticesBetweenCycles(a, b);
        }
        else {
            const int cyc = rand() % 2;
            int a = rand() % currentSolution[cyc].getLength();
            int b = a;

            while(a == b){
                b = rand() % currentSolution[cyc].getLength();
            }

            if(a > b){
                std::swap(a, b);
            }

            if(availableMoveTypes[op] == Solution2Cycles::SWAP_2_EDGES){

                currentSolution.swap2Edges(a, b, &currentSolution[cyc]);
            }
            else if(availableMoveTypes[op] == Solution2Cycles::SWAP_2_VERTICES){

                currentSolution.swap2VerticesInCycle(a, b, &currentSolution[cyc]);
            }
        }

        int cost = currentSolution.getTotalCost();
        if(cost < bestSolution.getTotalCost()){

            bestSolution = currentSolution;
        }

        auto end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void AlgorithmBlindRunner::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmBlindRunner::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}