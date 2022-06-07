#ifndef MY_ALGORITHM_HPP
#define MY_ALGORITHM_HPP

#include "algorithm2cyclesMeta.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"
#include "../util_functions.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <chrono>

class MyAlgorithm : public Algorithm2cyclesMeta {

private:

    const Solution2Cycles * startSolution = nullptr;
    int MAX_ITERATIONS = 1e4;
    Solution2Cycles * bestFoundSolution = nullptr;
    std::vector<int> availableMoveTypes;

public:

    MyAlgorithm(Solution2Cycles * startSolution){
        this->startSolution = startSolution;
    }

    virtual ~MyAlgorithm(){
        if(this->bestFoundSolution != nullptr){
            delete this->bestFoundSolution;
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "my_algorithm";}
    void setAvailableMoveTypes(std::vector<int>) override;
    void setStartingSolution(const Solution2Cycles *) override;
    std::vector<std::pair<int, int> > find_bridges(std::vector<std::vector<int> > &);
    std::vector<int> find_articulation_points(std::vector<std::vector<int> > &);
};

#endif