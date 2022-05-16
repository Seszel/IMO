#ifndef ALGORITHM_SMALL_PERTURBATION_HPP
#define ALGORITHM_SMALL_PERTURBATION_HPP

#include "algorithm2cyclesMeta.hpp"
#include "algorithmLocalSteepest.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"
#include "util_functions.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <unordered_map>

class AlgorithmSmallPerturbation : public Algorithm2cyclesMeta {

private:

    const Solution2Cycles * startSolution = nullptr;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes;

    void perturbate(Solution2Cycles &, int, const InstanceTSP &);

public:

    AlgorithmSmallPerturbation(Solution2Cycles * startSolution){
        this->startSolution = startSolution;
    }

    virtual ~AlgorithmSmallPerturbation(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "small_perturbation";}
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;
};

#endif