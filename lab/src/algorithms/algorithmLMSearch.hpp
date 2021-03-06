#ifndef ALGORITHM_LM_SEARCH_HPP
#define ALGORITHM_LM_SEARCH_HPP

#include "algorithm2cyclesMeta.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"
#include "util_functions.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <unordered_map>

class AlgorithmLMSearch : public Algorithm2cyclesMeta {

private:

    const Solution2Cycles * startSolution = nullptr;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes;

    void updateLM(std::unordered_map<size_t, std::pair<Move, int> >&, Move, Solution2Cycles &);

public:

    AlgorithmLMSearch(Solution2Cycles * startSolution){
        this->startSolution = startSolution;
    }

    virtual ~AlgorithmLMSearch(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "lm_search";}
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;
};

#endif