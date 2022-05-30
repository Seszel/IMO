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

std::mutex lp_job_mutex;
int iteration = 0;

const int THREADS_NUM = 8;

const int NUMBER_OF_ITERATIONS = 8;

auto alg_random = AlgorithmRandom();
auto alg_cyc_exp = AlgorithmCycleExpansion();
auto alg_greedy_nn = AlgorithmGreedyNN();
auto alg_lps = AlgorithmLocalSteepest(nullptr);
auto alg_lpg = AlgorithmLocalGreedy(nullptr);

std::vector<std::pair<float, float> > dataA(NUMBER_OF_ITERATIONS, {0,0});
std::vector<std::pair<float, float> > dataB(NUMBER_OF_ITERATIONS, {0,0});

std::vector<Solution2Cycles> solutionsA(NUMBER_OF_ITERATIONS);
std::vector<Solution2Cycles> solutionsB(NUMBER_OF_ITERATIONS);

float correlation(Solution2Cycles a, Solution2Cycles b, std::string type){

    if(type == "edges"){

        auto common_edges = a.sumEdges(b);
        return common_edges.size() / 400.0;
    }
    else if(type == "vertices"){

        int s, t;
        s = getNumberOfCommonVertices(a.getCycles()[0].getVertices(), b.getCycles()[0].getVertices()) +
            getNumberOfCommonVertices(a.getCycles()[1].getVertices(), b.getCycles()[1].getVertices());

        t = getNumberOfCommonVertices(a.getCycles()[0].getVertices(), b.getCycles()[1].getVertices()) +
            getNumberOfCommonVertices(a.getCycles()[1].getVertices(), b.getCycles()[0].getVertices());

        return std::max(s, t) / 200.0;
    }
    return 0;
}

void local_search(std::string alg_name, InstanceTSP A, InstanceTSP B){
 
    int it = -1;
    Solution2Cycles sol;

    lp_job_mutex.lock();
    it = iteration;
    iteration++;
    lp_job_mutex.unlock();   

    while(it < NUMBER_OF_ITERATIONS){ 

        std::cerr << it << " ";
        sol = alg_random.run(A);
        alg_lps.setStartingSolution(&sol);
        sol = alg_lps.run(A);
        solutionsA[it] = sol;
        dataA[it].first = sol.getTotalCost();

        sol = alg_random.run(B);
        alg_lps.setStartingSolution(&sol);
        sol = alg_lps.run(B);
        solutionsB[it] = sol;
        dataB[it].first = sol.getTotalCost();

        lp_job_mutex.lock();
        it = iteration;
        iteration++;
        lp_job_mutex.unlock();  
    }
}

int main(){

    srand(time(NULL));

    Solution2Cycles solution;

    std::fstream file;

    auto path = getPathToWorkspaceFolder();

    auto t = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(t);

    file.open(path + "resultFiles/" + std::string(std::ctime(&timestamp)) + ".json", std::ios::out);


    //load instances
    auto pathA = getPathToWorkspaceFolder();
    pathA += "data/kroa200.tsp";
    auto pathB = getPathToWorkspaceFolder();
    pathB += "data/krob200.tsp";

    InstanceTSP A, B;
    A.readFromFile(pathA);
    B.readFromFile(pathB);
    std::cout << "Data loaded." << std::endl;

    json algorithmsData;

    std::vector<std::string> alg_types = {"lp", "greedy", "cyc_exp"};
    std::vector<std::string> corr_types = {"edges", "vertices"};

    for(auto alg_type : alg_types){
        // algorithmsData[alg_type] = {}
        for(auto corr_type : corr_types){
            iteration = 0;
            std::thread threads[THREADS_NUM];
            for(int i = 0; i < THREADS_NUM; i++){
                threads[i] = std::thread(local_search, alg_type, A, B);
            }

            for(int i = 0; i < THREADS_NUM; i++){
                threads[i].join();
            }
            for(int i = 0; i < THREADS_NUM; i++){
                // threads[i].detach();
            }

            for(int i = 0; i < NUMBER_OF_ITERATIONS; i++){
                float avga = 0;
                float avgb = 0;
                for(int j = 0; j < NUMBER_OF_ITERATIONS; j ++){
                    if(j == i)
                        continue;
                    
                    avga += correlation(solutionsA[i], solutionsA[j], corr_type);
                    avgb += correlation(solutionsB[i], solutionsB[j], corr_type);
                }
                dataA[i].second = avga / (NUMBER_OF_ITERATIONS - 1);
                dataB[i].second = avgb / (NUMBER_OF_ITERATIONS - 1);
            }
            algorithmsData[alg_type][corr_type]["kroA200"] = dataA;
            algorithmsData[alg_type][corr_type]["kroB200"] = dataB;
        }
    }

    file << algorithmsData.dump();
    file.close();

    return 0;
}