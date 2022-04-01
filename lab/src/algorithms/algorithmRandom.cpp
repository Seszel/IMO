#include "algorithmRandom.hpp"

const Solution2Cycles AlgorithmRandom::run(const InstanceTSP & instance){
    
    Solution2Cycles solution;

    auto currentCycle = solution.addCycle();

    std::vector<int> v;v.resize(instance.dimension);

    for(int i = 0; i < v.size(); i ++)
        v[i] = i;

    for(int i = 0; i < 50; i++){

        int r = rand()%v.size();

        currentCycle->pushBackVertex(v[r]);

        v.erase(v.begin() + r);
    }

    currentCycle = solution.addCycle();

    for(int i = 0; i < 50; i++){

        int r = rand() % v.size();

        currentCycle->pushBackVertex(v[r]);

        v.erase(v.begin() + r);
    }

    solution.setAlgorithmType("random");
    solution.setInstanceName(instance.getName());

    solution.setInstance(instance);

    return solution;
}

const std::string AlgorithmRandom::getName(){
    
    return "random";
}