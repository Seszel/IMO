#ifndef ALGORITHM_HEA_HPP
#define ALGORITHM_HEA_HPP

#include "algorithm2cyclesMeta.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"
#include "algorithmRandom.hpp"
#include "algorithmLocalSteepest.hpp"
#include "algorithmCycleExpansion.hpp"
#include "algorithmGreedyNN.hpp"
#include "algorithmLocalGreedy.hpp"
#include "algorithmLMSearch.hpp"

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
    int max_time = 60000;
    bool lp_after_combine = false;
    std::string alg_init_pop = "cyc_exp";

public:

    int number_of_iterations = 0;

    AlgorithmHEA(Solution2Cycles * startSolution, int pop_size, int max_time, bool lp_after_combine,
                                std::string alg_init_pop){
        this->startSolution = startSolution;
        this->max_time = max_time;
        this->population_size = pop_size;
        this->lp_after_combine = lp_after_combine;
        this->alg_init_pop = alg_init_pop;
    }

    virtual ~AlgorithmHEA(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "HEA" + this->alg_init_pop + "_" + std::to_string(int(population_size)) + "_" + std::to_string(lp_after_combine);}
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;

    void repair(Solution2Cycles &, const InstanceTSP &, std::vector<int>);
    void perturbate(Solution2Cycles &, int, const InstanceTSP &);
};

#endif