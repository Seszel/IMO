#ifndef ALGORITHM_LARGE_SCALE_NEIGHBORHOOD_HPP
#define ALGORITHM_LARGE_SCALE_NEIGHBORHOOD_HPP

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

class AlgorithmLargeScaleNeighborhood : public Algorithm2cyclesMeta {

private:

    int K = 10;
    const Solution2Cycles * startSolution = nullptr;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes;

    std::vector<int> destroy(Solution2Cycles &, const InstanceTSP &, int, int);
    void repair(Solution2Cycles &, const InstanceTSP &, std::vector<int>);

public:

    AlgorithmLargeScaleNeighborhood(Solution2Cycles * startSolution, int K){
        this->startSolution = startSolution;
        this->K = K;
    }

    virtual ~AlgorithmLargeScaleNeighborhood(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "large_scale_neighborhood_" + std::to_string(this->K);}
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;
};

#endif