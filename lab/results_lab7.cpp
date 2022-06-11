#include "src/allalgorithms.hpp"
#include "src/allinstances.hpp"
#include "src/allsolutions.hpp"
#include "lib/json/single_include/nlohmann/json.hpp"
#include "src/util_functions.hpp"

#include <chrono>
#include <unistd.h>

#include <iostream>
#include <fstream>

using namespace nlohmann;

typedef std::vector<int> NEIGHBOURHOOD;

//to jest zmienna, która oznacza ile iteracji będziemy wykonywać, u nas jest to 100 razy
const int NUMBER_OF_ITERATIONS = 1;

int main(){

    srand(time(NULL));

    Solution2Cycles solution;

    std::fstream file;

    auto path = getPathToWorkspaceFolder();

    file.open(path + "resultFiles/results_lab_7.json", std::ios::out);

    std::vector<Algorithm2cycles *> algs_start;
    // algs_start.push_back(new AlgorithmCycleExpansion());
    // algs_start.push_back(new AlgorithmSeparateCycles());
    algs_start.push_back(new AlgorithmRandom());

    std::vector<Algorithm2cyclesMeta *> algs_meta;
    // algs_meta.push_back(new AlgorithmHEA(nullptr, 20, 10000, false, "cyc_exp", 2, 2));
    // algs_meta.push_back(new AlgorithmHEA(nullptr, 20, 10000, false, "cyc_exp", 7, 2));
    algs_meta.push_back(new AlgorithmHEA(nullptr, 7, 300000, true, "cyc_exp", 1,1,3));


    std::map<std::string, NEIGHBOURHOOD> neighbourhoods = {
        {"edges",{Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_BETWEEN_CYCLES}},
        // {"vertices", {Solution2Cycles::SWAP_BETWEEN_CYCLES, Solution2Cycles::SWAP_2_VERTICES}},
        // {"all", {Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_BETWEEN_CYCLES, Solution2Cycles::SWAP_2_VERTICES}}
    };

    //load instances
    auto pathA = getPathToWorkspaceFolder();
    pathA += "data/kroa200.tsp";
    auto pathB = getPathToWorkspaceFolder();
    pathB += "data/krob200.tsp";

    std::vector<InstanceTSP> instances;instances.resize(2);
    instances[0].readFromFile(pathA);
    instances[1].readFromFile(pathB);
    std::cout << "Data loaded." << std::endl;

    auto myalg = MyAlgorithm(nullptr);
    auto hea = AlgorithmHEA(nullptr, 20, 60000, true, "regret");
    auto cyc_exp = AlgorithmCycleExpansion();

    Solution2Cycles sol;
    int iterations = 10;

    for(int i = 0; i < iterations; i++){
        sol = hea.run(instances[0]);
        std::cerr << sol.getTotalCost() << " ";

    }
    std::cerr << std::endl;

    for(int i = 0; i < iterations; i++){
        sol = hea.run(instances[1]);
        std::cerr << sol.getTotalCost() << " ";
    }
    
    auto regret = Algorithm2Regret();
    float alpha, beta;
    alpha = 1.0f;
    beta = 1.0f;
    regret.setParams(1.0f,1.0f);
    sol = regret.run(instances[0]);
    int arange = 15;
    struct score {
        float avg;
        float alpha;
        float beta;
    };
    // score best_score = {1e9, 1.f, 1.f};
    // for(int i = 0; i < arange; i++){
    //     for(int j = 0; j < arange; j++){
    //         float sum = 0;
    //         float a = alpha / arange * float(i);
    //         float b = beta / arange * float(j);
    //         for(int k = 0; k < iterations; k++){
    //             regret.setParams(a, b);
    //             sol = regret.run(A);                
    //             sum += sol.getTotalCost();

    //             sol = regret.run(B);
    //             sum += sol.getTotalCost();
    //         }
    //         float avg = sum / (iterations * 2);
    //         if(avg < best_score.avg){
    //             best_score.avg = avg;
    //             best_score.alpha = a;
    //             best_score.beta = b;
    //         }
    //         std::cerr << "regret (" + std::to_string(a) << ", " + std::to_string(b) << "): " << avg << std::endl;            
    //     }
    // }
    // std::cerr << "best score: (" << std::to_string(best_score.avg) << 
    //     ", " << std::to_string(best_score.alpha) << ", " << 
    //     std::to_string(best_score.beta) << ")" << std::endl;
    

    return 0;
}