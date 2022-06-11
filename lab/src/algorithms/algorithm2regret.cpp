#include "algorithm2regret.hpp"

const Solution2Cycles Algorithm2Regret::run(const InstanceTSP & instance){

    struct helper
    {
        int vertex;
        int pos;
        int cost;
    };
    

    Solution2Cycles finalSolution;

    std::vector<bool > visited;

    visited.resize(instance.dimension, false);

    int cycleLength = instance.dimension/2;

    finalSolution.setInstance(instance);

    while(std::find(visited.begin(), visited.end(), false)!= visited.end()){

        //choose random startin vertex
        int randomStart = rand() % instance.dimension;
        while(visited[randomStart] == true)
            randomStart = rand() % instance.dimension;

        //find closest neighbor
        Cycle * currentCycle = finalSolution.addCycle();

        currentCycle->pushBackVertex(randomStart);
        visited[randomStart] = true;

        int secondVertex = this->findClosestVertex(randomStart, instance, visited);
        visited[secondVertex] = true;
        
        currentCycle->pushBackVertex(secondVertex);
        
        //for each cycle
        while(currentCycle->getLength() < cycleLength){

            int maxRegret = -1e9;
            int pos;
            int next;
            int cost = std::numeric_limits<int>::max();
            for(int v = 0; v < instance.dimension; v++){

                if(visited[v] == true){
                    continue;
                }

                std::vector<helper> insCosts;
                insCosts.resize(currentCycle->getLength());

                for(int insPos = 0; insPos < currentCycle->getLength(); insPos++){

                    int a = (currentCycle->getLength() + insPos - 1) % currentCycle->getLength();
                    int prev = (*currentCycle)[a];
                    int succ = (*currentCycle)[insPos];
                    int diff = instance.matrix[prev][v] + instance.matrix[v][succ] - instance.matrix[prev][succ];

                    insCosts[insPos] = {v, insPos, diff};
                }

                std::sort(insCosts.begin(), insCosts.end(), [](const helper & a, const helper & b) -> bool{
                    return a.cost < b.cost;
                });

                int regret = alpha * insCosts[1].cost - beta * insCosts.front().cost;
                if(regret > maxRegret){
                    maxRegret = regret;
                    pos = insCosts.front().pos;
                    cost = insCosts.front().cost;
                    next = insCosts.front().vertex;
                } else if(regret == maxRegret){
                    
                    if(insCosts.front().cost < cost){
                        maxRegret = regret;
                        pos = insCosts.front().pos;
                        cost = insCosts.front().cost;
                        next = insCosts.front().vertex;
                    }
                }
            }

            currentCycle->addVertex(pos, next);
            visited[next]= true;
        }
    }

    finalSolution.setAlgorithmType("2-regret");
    finalSolution.setInstanceName(instance.getName());

    return finalSolution;
}

void Algorithm2Regret::setParams(const float a, const float b){

    this->alpha = a;
    this->beta = b;
}