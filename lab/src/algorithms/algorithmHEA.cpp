#include "algorithmHEA.hpp"

const Solution2Cycles AlgorithmHEA::run(const InstanceTSP & instance){

    int duration = 0;

    auto start = std::chrono::steady_clock::now();

    auto alg_cycexp = AlgorithmCycleExpansion();
    alg_cycexp.freq = this->cyc_exp_freq;
    alg_cycexp.random_upper_bound = this->cyc_exp_ub;
    auto alg_greedy = AlgorithmGreedyNN();
    auto alg_random = AlgorithmRandom();
    auto alg_regret = Algorithm2Regret();
    alg_regret.setParams(5.33, 7.33);
    auto alg_lp = AlgorithmLocalSteepest(nullptr);
    auto alg_gp = AlgorithmLocalGreedy(nullptr);
    auto alg_lm = AlgorithmLMSearch(nullptr);

    // generate initial population
    std::vector<Solution2Cycles> population;
    for(int i = 0; i < N_BATCHES * population_size; i++){
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
        else if(this->alg_init_pop == "regret"){
            sol = alg_regret.run(instance);
        }
        population.push_back(sol);
    }
    auto bestSolution = population[0];

    std::vector<Solution2Cycles *> pop_ptr;
    for(int i = 0; i < population_size * N_BATCHES; i++){
        pop_ptr.push_back(&population[i]);
    }

    std::vector<std::vector<std::vector<float> > > cov_matrix;
    cov_matrix.resize(population_size);
    for(auto & r : cov_matrix)
        r.resize(population_size);
    
    for(int i = 0; i < population_size; i ++){
        for(int j = i; j < population_size; j++){
            for(int k = 0; k < N_BATCHES; k++){
                cov_matrix[i][j].resize(N_BATCHES);
                cov_matrix[j][i].resize(N_BATCHES);
                if(i == j){
                    cov_matrix[i][j][k] = 0;
                    continue;
                }
                float cov = population[k*population_size + i].sumEdges(population[k*population_size + j]).size() / 400.0;
                cov_matrix[i][j][k] = cov;
                cov_matrix[j][i][k] = cov;                
            }

        }
    }

    int iteration = 0;
    int n_iter_without_impr = 0;

    int current_batch = 0;

    while(duration < max_time){

        int dad_ind = rand() % population_size;
        int mom_ind = rand() % population_size;
        while(mom_ind == dad_ind)
            mom_ind = rand() % population_size;

        auto dad = pop_ptr[current_batch * population_size + dad_ind], mom = pop_ptr[current_batch * population_size + mom_ind];
        auto child = *dad;

        auto edges_to_delete = dad->minusEdges(*mom);
        
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

        std::sort(pop_ptr.begin() + current_batch * population_size, pop_ptr.begin() + (current_batch + 1) * population_size, [](Solution2Cycles * a, Solution2Cycles * b){
            return a->getTotalCost() < b->getTotalCost();
        });

        if(child.getTotalCost() < pop_ptr[(current_batch + 1) * population_size - 1]->getTotalCost()){

            std::vector<float> cov_vector(population_size, 0);
            int d = &pop_ptr[(current_batch + 1) * population_size - 1] - &pop_ptr[current_batch * population_size];
            float _min = RAND_MAX;
            for(int i = 0; i < population_size; i++){
                float cov = population[i].sumEdges(population[d]).size() / 400.0;
                cov_vector[i] = cov;
                if(_min > cov){
                    _min = cov;
                }
            }
            if(_min < 0.8){

                *pop_ptr.back() = child;

                // update cov matrix

                for(int j = 0; j < population_size; j++){
                    cov_matrix[d][j][current_batch] = cov_vector[j];
                    cov_matrix[j][d][current_batch] = cov_vector[j];
                }  
                            
            }
            if(n_iter_without_impr > 20 && iteration % 20 == 0) {
                // int from = population_size/2;
                // while(from < pop_ptr.size()){
                //     auto sol = alg_cycexp.run(instance);
                //     *pop_ptr[from] = sol;
                //     from++;
                // }
                std::cerr << "|";
                std::random_shuffle(pop_ptr.begin(), pop_ptr.end());                    
                // this->perturbate(child, 8, instance);
                // alg_lp.setStartingSolution(&child);
                // child = alg_lp.run(instance);

            }
        }
        int r;
        int __min = RAND_MAX;
        for(int i = 0; i < pop_ptr.size(); i++)
            if(pop_ptr[i]->getTotalCost() < __min){
                __min = pop_ptr[i]->getTotalCost();
                r = i;
            }

        if(pop_ptr[r]->getTotalCost() < bestSolution.getTotalCost()){
            bestSolution = *pop_ptr[current_batch * population_size];
            std::cerr << "=";
            n_iter_without_impr = -1;
        }

        auto end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
        iteration += 1;
        n_iter_without_impr += 1;

        current_batch = (current_batch + 1) % N_BATCHES;
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

const Solution2Cycles AlgorithmHEA::run1cycle(const InstanceTSP & instance){

    
}