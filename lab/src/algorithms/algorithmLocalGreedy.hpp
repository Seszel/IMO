#ifndef ALGORITHM_LOCAL_GREEDY_HPP
#define ALGORITHM_LOCAL_GREEDY_HPP


#include "algorithm2cyclesMeta.hpp"
#include "../allinstances.hpp"
#include "../allsolutions.hpp"

#include <vector>
#include <algorithm>

class AlgorithmLocalGreedy : public Algorithm2cyclesMeta{

private:

    const Solution2Cycles * startingSolution = nullptr;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes = {
        Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_2_VERTICES, Solution2Cycles::SWAP_BETWEEN_CYCLES
    };

public:

    AlgorithmLocalGreedy(Solution2Cycles * solution){

        this->startingSolution = solution;
    }

    ~AlgorithmLocalGreedy(){
        
        if(this->bestFoundSolution != nullptr){
            delete bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "local_greedy";}
    void setAvailableMoveTypes(std::vector<int>);
    void setStartingSolution(const Solution2Cycles * s){ this->startingSolution = s; }
};

#endif