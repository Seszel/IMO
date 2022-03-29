#ifndef ALGORITHM_LOCAL_GREEDY_HPP
#define ALGORITHM_LOCAL_GREEDY_HPP


#include "algorithm2cycles.hpp"
#include "../allinstances.hpp"
#include "../allsolutions.hpp"

#include <vector>
#include <algorithm.hpp>

class AlgorithmLocalGreedy : public Algorithm2cycles{

private:

    Solution2Cycles * startingSolution = nullptr;
    Solution2Cycles * bestFoundSolution = nullptr;

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

};

#endif