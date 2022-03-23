#include "src/allalgorithms.hpp"
#include "src/allinstances.hpp"
#include "src/allsolutions.hpp"
#include "lib/json/single_include/nlohmann/json.hpp"

#include <iostream>
#include <fstream>

using namespace nlohmann;

const int NUMBER_OF_ITERATIONS = 100;

int main(){

    srand(time(NULL));

    Solution2Cycles solution;

    std::fstream file;
    file.open("../resultFiles/test.json", std::ios::out);

    std::vector<Algorithm2cycles *> algs;
    algs.push_back(new AlgorithmGreedyNN());
    algs.push_back(new AlgorithmCycleExpansion());
    algs.push_back(new Algorithm2Regret());

    //load instances
    std::vector<InstanceTSP> instances;instances.resize(2);
    instances[0].readFromFile("/home/piotr/Dokumenty/SI/imo/IMO/lab1/data/kroa100.tsp");
    instances[1].readFromFile("/home/piotr/Dokumenty/SI/imo/IMO/lab1/data/krob100.tsp");
    std::cout << "Data loaded." << std::endl;

    json algorithmsData;

    algorithmsData["algorithm"] = {};

    Solution2Cycles best;
    //generate results for greedy
    for(auto algorithm : algs){

        std::vector<json> tmp;

        for(auto & instance : instances){

            int min = 1e9;
            int max = -1;
            int avg = 0;
            
            for(int i = 0; i < NUMBER_OF_ITERATIONS; i++){

                Solution2Cycles s = algorithm->run(instance);

                int cost = s.getTotalCost();
                if(cost < min){

                    best = s;
                    min = cost;
                }
                avg += cost;
                if(cost > max){

                    max = cost;
                }                
            }
            avg /= NUMBER_OF_ITERATIONS;
            auto best_json = json::parse(best.saveAsJson());

            best_json["instance"]["avg"] = avg;
            best_json["instance"]["min"] = min;
            best_json["instance"]["max"] = max;
            tmp.push_back(best_json["instance"]);
        }
        json h;
        h["instance"] = tmp;
        h["type"] = algorithm->getName();
        algorithmsData["algorithm"].push_back(h);
    }

    file << algorithmsData.dump();
    file.close();

    return 0;
}