#include "algorithmLocalGreedy.hpp"

const Solution2Cycles AlgorithmLocalGreedy::run(const InstanceTSP &){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startingSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startingSolution);

    bool improvementFound = false;
}