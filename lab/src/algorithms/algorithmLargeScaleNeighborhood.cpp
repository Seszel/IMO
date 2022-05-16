#include "algorithmLargeScaleNeighborhood.hpp"

const Solution2Cycles AlgorithmLargeScaleNeighborhood::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    int duration;
    auto start = std::chrono::steady_clock::now();
    int K = 20;

    while(duration < 5000){

        auto missing = this->destroy(currentSolution, instance, K);
        this->repair(currentSolution, instance, missing);

        auto end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void AlgorithmLargeScaleNeighborhood::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmLargeScaleNeighborhood::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}

std::vector<int> AlgorithmLargeScaleNeighborhood::destroy(Solution2Cycles & sol, const InstanceTSP & instance, int K){

    int start_vertex = std::rand() % sol[0].getLength();
    int cn = std::rand() % 2;
    int v = sol[cn][start_vertex];

    auto closest = this->findKClosestVertices(v, K, instance);
    auto clos_indx = this->findVertices(closest, sol);

    for(auto & p : clos_indx){
        sol[p.first].removeVertex(p.second);
    }

    return closest;
}

void AlgorithmLargeScaleNeighborhood::repair(Solution2Cycles & sol, const InstanceTSP & instance, std::vector<int> missing){

    struct Tuple {
        int v;
        int pos;
        int cycle;
        int delta;
    };

    std::vector<Tuple> insertions;
    for(auto v : missing){

        // for each cycle
        for(int i = 0; i < sol.getCycles().size(); i++){

            // for each position in cycle
            for(int pos = 0; pos < sol[i].getLength(); pos ++){

                int suc = sol[i][(pos + 1) % sol[i].getLength()];
                int pre = sol[i][(pos + sol[i].getLength() - 1) % sol[i].getLength()];

                int diff = instance.matrix[pre][v] + instance.matrix[v][suc] - instance.matrix[pre][suc];

                insertions.push_back({v, pos, i, diff});
            }
        }
    }

    std::sort(insertions.begin(), insertions.end(), [](const Tuple a, const Tuple b){
        return a.delta < b.delta;
    });

    while(missing.size() > 0){
        for(auto & ins : insertions){
            if(sol[ins.cycle].getLength() < instance.dimension/2 && std::find(missing.begin(), missing.end(), ins.v) != missing.end()){
                sol[ins.cycle].addVertex(ins.pos, ins.v);
                auto it = std::find(missing.begin(), missing.end(), ins.v);
                missing.erase(it);
            }
        }
    }
}

