#ifndef ALGORITHM_BLIND_RUNNER_HPP
#define ALGORITHM_BLIND_RUNNER_HPP

#include "algorithm2cyclesMeta.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>

class AlgorithmBlindRunner : public Algorithm2cyclesMeta {

private:

    const Solution2Cycles * startSolution = nullptr;
    int MAX_ITERATIONS = 1e4;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes;

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
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;
};

#endif