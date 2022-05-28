#ifndef ALGORITHM_LOCAL_CANDIDATES_HPP
#define ALGORITHM_LOCAL_CANDIDATES_HPP


#include "algorithm2cyclesMeta.hpp"
#include "../allinstances.hpp"
#include "../allsolutions.hpp"

#include <vector>
#include <algorithm>

class AlgorithmLocalCandidates : public Algorithm2cyclesMeta{

private:

    int k = 10;

    Solution2Cycles * bestSolution = nullptr;
    const Solution2Cycles * startSolution = nullptr;

    std::vector<int> availableMoveTypes = {
        Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_2_VERTICES, Solution2Cycles::SWAP_BETWEEN_CYCLES
    };

public:


    AlgorithmLocalCandidates(const Solution2Cycles * startSolution, int k){

        this->startSolution = startSolution;
        this->k = k;
    }

    virtual ~AlgorithmLocalCandidates(){

        if(bestSolution != nullptr){
            delete this->bestSolution; 
        }
    }

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "local_candidates_" + std::to_string(k);}
    void setAvailableMoveTypes(std::vector<int>);
    void setStartingSolution(const Solution2Cycles * s){ this->startSolution = s; }
    std::vector<std::vector<int > > findKClosestForAll(int, const InstanceTSP &, Solution2Cycles &);
    // vector of pairs closest vertices to all vertices
    // vector<pair(vertex cycle, vector<pair(vertex cycle, vertex)>)>
};

#endif