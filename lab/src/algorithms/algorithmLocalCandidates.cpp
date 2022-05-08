#include "algorithmLocalCandidates.hpp"

std::vector<std::vector<int > > AlgorithmLocalCandidates::findKClosestVertices(int k, const InstanceTSP & instance) {

    int min = RAND_MAX;
    std::vector<std::vector<int > > closestVertices;
    std::vector<int > temp(instance.dimension);

    for (int v=0; v<instance.dimension; v++){
        std::iota(temp.begin(), temp.end(),0);

        std::sort(temp.begin(), temp.end(), [&](int a, int b){
            return instance.matrix[v][a] < instance.matrix[v][b];
        });

        closestVertices.push_back(std::vector<int >(temp.begin(), temp.begin() + k));
    }
    return closestVertices;

}

const Solution2Cycles AlgorithmLocalCandidates::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startSolution);

    auto closestVertices = findKClosestVertices(10, instance);



    return currentSolution;

}

void AlgorithmLocalCandidates::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

    