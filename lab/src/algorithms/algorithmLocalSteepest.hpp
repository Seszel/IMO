#ifndef ALGORITHM_LOCAL_STEEPEST_HPP
#define ALGORITHM_LOCAL_STEEPEST_HPP

#include "algorithm2cyclesMeta.hpp"
#include "../allinstances.hpp"
#include "../allsolutions.hpp"


#include <vector>
#include <algorithm>
#include <string>


class AlgorithmLocalSteepest : public Algorithm2cyclesMeta{

private:


    Solution2Cycles * bestSolution = nullptr;
    const Solution2Cycles * startSolution = nullptr;

    std::vector<int> availableMoveTypes = {
        Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_2_VERTICES, Solution2Cycles::SWAP_BETWEEN_CYCLES
    };

public:
    

    AlgorithmLocalSteepest(const Solution2Cycles * startSolution){

        this->startSolution = startSolution;
    }

    virtual ~AlgorithmLocalSteepest(){

        if(bestSolution != nullptr){
            delete this->bestSolution; 
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "local_steepest";}
    void setAvailableMoveTypes(std::vector<int>);
    void setStartingSolution(const Solution2Cycles * s){ this->startSolution = s; }
};

#endif