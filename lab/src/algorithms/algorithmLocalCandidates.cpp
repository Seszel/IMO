#include "algorithmLocalCandidates.hpp"

std::vector<int > AlgorithmLocalCandidates::findNClosestVertices(int v, int n, const InstanceTSP & instance) {

    int min = RAND_MAX;
    std::vector<int > closestVertices(instance.dimension);
    std::iota(closestVertices.begin(), closestVertices.end(),0);

    // for (int k=0; k<20; k++){
    //     std::cout << closestVertices[k] << std::endl;
    // }

    std::sort(closestVertices.begin(), closestVertices.end(), [&](int a, int b){
        return instance.matrix[v][a] < instance.matrix[v][b];
    });

    // for (int k=0; k<20; k++){
    //     std::cout << closestVertices[k] << std::endl;
    // }

    return closestVertices;

}

const Solution2Cycles AlgorithmLocalCandidates::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startSolution);

    auto closestVertices = findNClosestVertices(1, 10, instance);



    return currentSolution;

}

void AlgorithmLocalCandidates::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

    