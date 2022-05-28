#include "algorithmLargeScaleNeighborhood.hpp"

const Solution2Cycles AlgorithmLargeScaleNeighborhood::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    int duration = 0;
    auto start = std::chrono::steady_clock::now();

    auto alg_steepest = AlgorithmLocalSteepest(this->startSolution);
    currentSolution = alg_steepest.run(instance);

    while(duration < 60000){

        auto missing = this->destroy(currentSolution, instance, K, 0);
        this->repair(currentSolution, instance, missing);

        if(currentSolution.getTotalCost() < bestSolution.getTotalCost()){
            bestSolution = currentSolution;
        }

        auto end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    this->bestFoundSolution = new Solution2Cycles(currentSolution);

    return bestSolution;
}

void AlgorithmLargeScaleNeighborhood::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmLargeScaleNeighborhood::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}

std::vector<int> AlgorithmLargeScaleNeighborhood::destroy(Solution2Cycles & sol, const InstanceTSP & instance, int K, int type){
        
    int start_vertex = std::rand() % sol[0].getLength();
    int cn = std::rand() % 2;
    int v = sol[cn][start_vertex];
    std::vector<std::pair<int, int> > clos_indx;
    std::vector<int> closest;

    if(type == 0){

        closest = this->findKClosestVertices(v, K, instance);
        clos_indx = this->findVertices(closest, sol);  
    }
    else {
        for(int i = 0; i < K; i++){
            
            clos_indx.push_back({cn, (start_vertex + i) % sol[cn].getLength()});
            closest.push_back(sol[cn][(start_vertex + i) % sol[cn].getLength()]);
        }
    }

    std::sort(clos_indx.begin(), clos_indx.end(), [](const std::pair<int, int> a, const std::pair<int, int> b){
        return a.second > b.second;
    });

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
    while(!missing.empty()){
        
        
        insertions.clear();insertions.shrink_to_fit();
        for(auto & v : missing){

            Tuple min_tuple;
            int min = RAND_MAX;
            // for each cycle
            for(int i = 0; i < sol.getCycles().size(); i++){
                
                if(sol[i].getLength() == instance.dimension/2)
                    continue;
                // for each position in cycle
                for(int pos = 0; pos < sol[i].getLength(); pos ++){

                    int suc = sol[i][(pos) % sol[i].getLength()];
                    int pre = sol[i][(pos + sol[i].getLength() - 1) % sol[i].getLength()];

                    int diff = instance.matrix[pre][v] + instance.matrix[v][suc] - instance.matrix[pre][suc];

                    if(diff < min){
                        min_tuple = {v, pos, i, diff};
                        min = diff;
                    }
                }
            }
            insertions.push_back(min_tuple);            
        }  

        std::sort(insertions.begin(), insertions.end(), [](const Tuple a, const Tuple b){
            return a.delta < b.delta;
        }); 

        auto ins = insertions[0];

        sol[ins.cycle].addVertex(ins.pos, ins.v);         

        auto it = std::find(missing.begin(), missing.end(), ins.v);
        missing.erase(it);

    }
}

