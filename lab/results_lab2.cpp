#include "src/allalgorithms.hpp"
#include "src/allinstances.hpp"
#include "src/allsolutions.hpp"
#include "lib/json/single_include/nlohmann/json.hpp"
#include "src/util_functions.hpp"

#include <iostream>
#include <fstream>

using namespace nlohmann;

typedef std::vector<int> NEIGHBOURHOOD;

const int NUMBER_OF_ITERATIONS = 2;

int main(){

    srand(time(NULL));

    Solution2Cycles solution;

    std::fstream file;

    auto path = getPathToWorkspaceFolder();

    file.open(path + "resultFiles/results_lab_2.json", std::ios::out);

    std::vector<Algorithm2cycles *> algs_start;
    std::vector<Algorithm2cyclesMeta *> algs_meta;
    algs_start.push_back(new AlgorithmGreedyNN());
    algs_start.push_back(new AlgorithmCycleExpansion());
    algs_start.push_back(new Algorithm2Regret());
    algs_start.push_back(new AlgorithmRandom());

    algs_meta.push_back(new AlgorithmLocalSteepest(nullptr));
    algs_meta.push_back(new AlgorithmLocalGreedy(nullptr));
    algs_meta.push_back(new AlgorithmBlindRunner(nullptr));

    std::map<std::string, NEIGHBOURHOOD> neighbourhoods = {
        {"edges",{Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_BETWEEN_CYCLES}},
        {"vertices", {Solution2Cycles::SWAP_BETWEEN_CYCLES, Solution2Cycles::SWAP_2_VERTICES}},
        {"all", {Solution2Cycles::SWAP_BETWEEN_CYCLES, Solution2Cycles::SWAP_2_VERTICES, Solution2Cycles::SWAP_2_EDGES}}
    };

    //load instances
    auto pathA = getPathToWorkspaceFolder();
    pathA += "data/kroa100.tsp";
    auto pathB = getPathToWorkspaceFolder();
    pathB += "data/krob100.tsp";

    std::vector<InstanceTSP> instances;instances.resize(2);
    instances[0].readFromFile(pathA);
    instances[1].readFromFile(pathB);
    std::cout << "Data loaded." << std::endl;

    json algorithmsData;

    algorithmsData["algorithm"] = {};

    Solution2Cycles best;

    std::vector<int> costs;
    //generate results for greedy
    for(auto algorithm : algs_start){

        for(auto algorithm_meta : algs_meta){

            std::cout << algorithm_meta->getName() << std::endl;

            for(const auto & nghbrhd : neighbourhoods){

                std::vector<json> tmp;

                for(auto & instance : instances){

                    int min = 1e9;
                    costs.clear();
                    
                    for(int i = 0; i < NUMBER_OF_ITERATIONS; i++){

                        Solution2Cycles s = algorithm->run(instance);

                        algorithm_meta->setStartingSolution(&s);

                        Solution2Cycles finals = algorithm_meta->run(instance); 

                        auto cost = finals.getTotalCost();

                        costs.push_back(cost);

                        if(cost < min){
                            min = cost;
                            best = finals;
                        }
                    }
                    auto best_json = json::parse(best.saveAsJson());

                    best_json["instance"]["f"] = costs;
                    tmp.push_back(best_json["instance"]);
                }
                json h;
                h["instance"] = tmp;
                h["type"] = algorithm->getName();
                h["type_meta"] = algorithm_meta->getName();
                h["neighbourhood"] = nghbrhd.first;
                algorithmsData["algorithm"].push_back(h);
            }
        }
    }

    file << algorithmsData.dump();
    file.close();

    return 0;
}