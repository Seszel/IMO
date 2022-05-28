#ifndef ALGORITHM_MULTIPLE_START_LOCAL_SEARCH_HPP
#define ALGORITHM_MULTIPLE_START_LOCAL_SEARCH_HPP

#include "algorithm2cyclesMeta.hpp"
#include "algorithmLocalSteepest.hpp"
#include "algorithmRandom.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <chrono>

class AlgorithmMultipleStartLocalSearch : public Algorithm2cyclesMeta {

private:

    const Solution2Cycles * startSolution = nullptr;
    int ITERATIONS = 20;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes;

public:

    AlgorithmMultipleStartLocalSearch(Solution2Cycles * startSolution){
        this->startSolution = startSolution;
    }

    virtual ~AlgorithmMultipleStartLocalSearch(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "msls";}
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;
};

#endif