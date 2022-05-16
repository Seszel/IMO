#include "algorithmSmallPerturbation.hpp"

const Solution2Cycles AlgorithmSmallPerturbation::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    AlgorithmLocalSteepest algoritmSteepest(&currentSolution);
    int duration = 0;
    int K = 10;

    auto start = std::chrono::steady_clock::now();

    while(duration < 5000){

        this->perturbate(currentSolution, K, instance);
        currentSolution = algoritmSteepest.run(instance);

        auto end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void AlgorithmSmallPerturbation::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmSmallPerturbation::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}

void AlgorithmSmallPerturbation::perturbate(Solution2Cycles & sol, int size, const InstanceTSP & instance){

    int start_vertex = std::rand() % sol[0].getLength();
    int cn = std::rand() % 2;
    int v = sol[cn][start_vertex];

    auto closest = this->findKClosestVertices(v, size, instance);
    auto clos_indx = this->findVertices(closest, sol);

    std::random_shuffle(closest.begin(), closest.end());

    for(int i = 0; i < size; i++){
        sol[clos_indx[i].first][clos_indx[i].second] = closest[i];
    }

    sol.calculateFromZero();
}