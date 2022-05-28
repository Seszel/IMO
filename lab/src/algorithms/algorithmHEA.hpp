#ifndef ALGORITHM_HEA_HPP
#define ALGORITHM_HEA_HPP

#include "algorithm2cyclesMeta.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"
#include "algorithmRandom.hpp"
#include "algorithmLocalSteepest.hpp"
#include "algorithmCycleExpansion.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <chrono>

class AlgorithmHEA : public Algorithm2cyclesMeta {

private:

    const Solution2Cycles * startSolution = nullptr;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes;

    int population_size = 20;

public:

    AlgorithmHEA(Solution2Cycles * startSolution){
        this->startSolution = startSolution;
    }

    virtual ~AlgorithmHEA(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "HEA";}
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;

    void repair(Solution2Cycles &, const InstanceTSP &, std::vector<int>);
};

#endif