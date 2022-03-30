#ifndef ALGORITHM_LOCAL_STEEPEST_HPP
#define ALGORITHM_LOCAL_STEEPEST_HPP

#include "algorithm2cycles.hpp"
#include "../allinstances.hpp"
#include "../allsolutions.hpp"


#include <vector>
#include <algorithm>
#include <string>


class AlgorithmLocalSteepest : public Algorithm2cycles{

private:

    const Solution2Cycles * startSolution = nullptr;
    Solution2Cycles * bestSolution = nullptr;

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
};

#endif