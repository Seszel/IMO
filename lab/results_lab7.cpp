#include "src/allalgorithms.hpp"
#include "src/allinstances.hpp"
#include "src/allsolutions.hpp"
#include "lib/json/single_include/nlohmann/json.hpp"
#include "src/util_functions.hpp"

#include <chrono>
#include <unistd.h>

#include <ctime>
#include <omp.h>
#include <mutex>
#include <thread>

#include <iostream>
#include <fstream>

using namespace nlohmann;

int main(){

    srand(time(NULL));

    Solution2Cycles solution;

    std::fstream file;

    auto path = getPathToWorkspaceFolder();

    // auto t = std::chrono::system_clock::now();
    // std::time_t timestamp = std::chrono::system_clock::to_time_t(t);

    // file.open(path + "resultFiles/" + std::string(std::ctime(&timestamp)) + ".json", std::ios::out);


    //load instances
    auto pathA = getPathToWorkspaceFolder();
    pathA += "data/kroa200.tsp";
    auto pathB = getPathToWorkspaceFolder();
    pathB += "data/krob200.tsp";

    InstanceTSP A, B;
    A.readFromFile(pathA);
    B.readFromFile(pathB);
    std::cout << "Data loaded." << std::endl;

    auto myalg = MyAlgorithm(nullptr);
    auto hea = AlgorithmHEA(nullptr, 20, 60000, true, "regret");
    auto cyc_exp = AlgorithmCycleExpansion();

    Solution2Cycles sol;
    int iterations = 10;

    for(int i = 0; i < iterations; i++){
        sol = hea.run(A);
        std::cerr << sol.getTotalCost() << " ";

    }
    std::cerr << std::endl;

    for(int i = 0; i < iterations; i++){
        sol = hea.run(B);
        std::cerr << sol.getTotalCost() << " ";
    }
    
    auto regret = Algorithm2Regret();
    float alpha, beta;
    alpha = 1.0f;
    beta = 1.0f;
    regret.setParams(1.0f,1.0f);
    sol = regret.run(A);
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