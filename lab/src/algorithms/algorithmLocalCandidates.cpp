#include "algorithmLocalCandidates.hpp"

const Solution2Cycles AlgorithmLocalCandidates::run(const InstanceTSP &){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startSolution);

    return currentSolution;

}

void AlgorithmLocalCandidates::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}