#include "algorithmHEA.hpp"

const Solution2Cycles AlgorithmHEA::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    int duration = 0;

    auto start = std::chrono::steady_clock::now();

    auto alg_start = AlgorithmCycleExpansion();
    // auto alg_start = AlgorithmRandom();
    // auto alg_lp = AlgorithmLocalSteepest(nullptr);

    // generate initial population
    std::vector<Solution2Cycles> population;
    for(int i = 0; i < population_size; i++){
        auto sol = alg_start.run(instance);
        population.push_back(sol);
    }

    std::vector<Solution2Cycles *> pop_ptr;
    for(int i = 0; i < population_size; i++){
        pop_ptr.push_back(&population[i]);
    }

    while(duration < 120000){

        int dad_ind = rand() % population_size;
        int mom_ind = rand() % population_size;
        while(mom_ind == dad_ind)
            mom_ind = rand() % population_size;

        auto dad = population[dad_ind], mom = population[mom_ind];
        auto child = dad;

        auto edges_to_delete = dad.minusEdges(mom);
        
        std::vector<int> vertices_to_delete = {}; 
        for(auto & edge : edges_to_delete){
            int u = edge.second.u;
            int v = edge.second.v;
            vertices_to_delete.push_back(u);
            vertices_to_delete.push_back(v);
        }
        std::sort(vertices_to_delete.begin(), vertices_to_delete.end());
        auto last = std::unique(vertices_to_delete.begin(), vertices_to_delete.end());
        vertices_to_delete.erase(last, vertices_to_delete.end());

        auto clos_indx = findVertices(vertices_to_delete, child);
        std::sort(clos_indx.begin(), clos_indx.end(), [](const std::pair<int, int> a, const std::pair<int, int> b){
            return a.second > b.second;
        });

        for(auto & p : clos_indx){
            child[p.first].removeVertex(p.second);
        }

        this->repair(child, instance, vertices_to_delete);

        std::sort(pop_ptr.begin(), pop_ptr.end(), [](Solution2Cycles * a, Solution2Cycles * b){
            return a->getTotalCost() < b->getTotalCost();
        });

        if(child.getTotalCost() < pop_ptr.back()->getTotalCost()){
            population.back() = child;
        }

        if(pop_ptr.front()->getTotalCost() < bestSolution.getTotalCost()){
            bestSolution = *pop_ptr.front();
        }

        auto end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void AlgorithmHEA::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmHEA::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}

void AlgorithmHEA::repair(Solution2Cycles & sol, const InstanceTSP & instance, std::vector<int> missing){

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