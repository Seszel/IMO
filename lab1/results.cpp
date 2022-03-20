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

    std::fstream fileA, fileB;
    fileA.open("../resultFiles/test.json", std::ios::out);

    //load instances
    InstanceTSP instanceA, instanceB;
    instanceA.readFromFile("/home/piotr/Dokumenty/SI/imo/IMO/lab1/data/kroa100.tsp");
    instanceB.readFromFile("/home/piotr/Dokumenty/SI/imo/IMO/lab1/data/krob100.tsp");
    std::cout << "Data loaded." << std::endl;

    json algorithmsData;

    std::vector<json> instances;

    json algorithmGreedy, algorithmExpansion, algorithmRegret;
    algorithmGreedy["type"] = "greedy";
    algorithmExpansion["type"] = "cycle_expansion";
    algorithmRegret["type"] = "regret";


    //generate results for greedy
    for(int i = 0; i < NUMBER_OF_ITERATIONS; i++){

        AlgorithmGreedyNN greedy;
        solution = greedy.run(instanceA);

        auto res = json::parse(solution.saveAsJson());

        instances.push_back(res["instance"]);
    }
    algorithmGreedy["instance"] = instances;
    algorithmsData["algorithm"].push_back(algorithmGreedy);
        
    instances.clear();instances.shrink_to_fit();
    for(int i = 0; i < NUMBER_OF_ITERATIONS; i++){

        AlgorithmCycleExpansion cycleExpansion;
        solution = cycleExpansion.run(instanceA);

        auto res = json::parse(solution.saveAsJson());

        instances.push_back(res["instance"]);
    }
    algorithmExpansion["instance"] = instances;
    algorithmsData["algorithm"].push_back(algorithmExpansion);

    instances.clear();instances.shrink_to_fit();

    // for(int i = 0; i < NUMBER_OF_ITERATIONS; i++){

    //     Algorithm2Regret regret;
    //     solution = regret.run(instanceA);

    //     auto res = json::parse(solution.saveAsJson());

    //     instances.push_back(res["instance"]);
    // }
    // algorithmRegret["instance"] = instances;
    // algorithmsData["algorithm"].push_back(algorithmRegret);

    fileA << algorithmsData.dump();
    fileA.close();

    return 0;
}