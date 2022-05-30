#include "algorithmHEA.hpp"

const Solution2Cycles AlgorithmHEA::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    int duration = 0;

    auto start = std::chrono::steady_clock::now();

    auto alg_cycexp = AlgorithmCycleExpansion();
    auto alg_greedy = AlgorithmGreedyNN();
    auto alg_random = AlgorithmRandom();
    auto alg_lp = AlgorithmLocalSteepest(nullptr);
    auto alg_gp = AlgorithmLocalGreedy(nullptr);
    auto alg_lm = AlgorithmLMSearch(nullptr);

    // generate initial population
    std::vector<Solution2Cycles> population;
    for(int i = 0; i < population_size; i++){
        Solution2Cycles sol;
        
        if(this->alg_init_pop == "cyc_exp")
            sol = alg_cycexp.run(instance);
        else if(this->alg_init_pop == "greedy")
            sol = alg_greedy.run(instance);
        else if(this->alg_init_pop == "lp"){
            sol = alg_random.run(instance);
            alg_lm.setStartingSolution(&sol);
            sol = alg_lm.run(instance);  
        }
        population.push_back(sol);
    }

    std::vector<Solution2Cycles *> pop_ptr;
    for(int i = 0; i < population_size; i++){
        pop_ptr.push_back(&population[i]);
    }

    std::vector<std::vector<float> > cov_matrix;
    cov_matrix.resize(population_size);
    for(auto & r : cov_matrix)
        r.resize(population_size);
    
    for(int i = 0; i < population_size; i ++){
        for(int j = i; j < population_size; j++){
            if(i == j){
                cov_matrix[i][j] = 0;
                continue;
            }
            int cov = population[i].sumEdges(population[j]).size() / 2.0;
            cov_matrix[i][j] = cov;
            cov_matrix[j][i] = cov;
        }
    }

    int iteration = 0;
    int n_iter_without_impr = 0;

    while(duration < max_time && n_iter_without_impr < population_size * population_size){

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

        if(this->lp_after_combine){
            alg_lp.setStartingSolution(&child);
            child = alg_lp.run(instance);
        }

        std::sort(pop_ptr.begin(), pop_ptr.end(), [](Solution2Cycles * a, Solution2Cycles * b){
            return a->getTotalCost() < b->getTotalCost();
        });

        if(child.getTotalCost() < pop_ptr.back()->getTotalCost()){

            std::vector<float> cov_vector(population_size, 0);
            int d = pop_ptr.back() - &population[0];
            float _min = RAND_MAX;
            for(int i = 0; i < population_size; i++){
                int cov = population[i].sumEdges(population[d]).size() / 2.0;
                cov_vector[i] = cov;
                if(_min > cov){
                    _min = cov;
                }
            }
            if(_min < 185){

                *pop_ptr.back() = child;

                // update cov matrix

                for(int j = 0; j < population_size; j++){
                    cov_matrix[d][j] = cov_vector[j];
                    cov_matrix[j][d] = cov_vector[j];
                }  
                            
            }
            else {
                this->perturbate(child, 8, instance);
                alg_lp.setStartingSolution(&child);
                child = alg_lp.run(instance);
            }
        }

        if(pop_ptr.front()->getTotalCost() < bestSolution.getTotalCost()){
            bestSolution = *pop_ptr.front();
            std::cerr << "=";
            n_iter_without_impr = -1;
        }

        auto end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
        iteration += 1;
        n_iter_without_impr += 1;

    }

    std::cerr << iteration << std::endl;
    this->number_of_iterations = iteration;
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

void AlgorithmHEA::perturbate(Solution2Cycles & sol, int size, const InstanceTSP & instance){

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