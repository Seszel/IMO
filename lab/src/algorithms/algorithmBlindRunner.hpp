#ifndef ALGORITHM_BLIND_RUNNER_HPP
#define ALGORITHM_BLIND_RUNNER_HPP

#include "algorithm2cycles.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"

class AlgorithmBlindRunner : public Algorithm2cycles{

private:

    Solution2Cycles * startSolution = nullptr;
    int MAX_ITERATIONS = 1e4;
    Solution2Cycles * bestFoundSolution = nullptr;

public:

    AlgorithmBlindRunner(Solution2Cycles * startSolution){
        this->startSolution = startSolution;
    }

    virtual ~AlgorithmBlindRunner(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "blind_runner";}
};

#endif