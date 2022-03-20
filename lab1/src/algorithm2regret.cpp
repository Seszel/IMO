#include "algorithm2regret.hpp"

const Solution2Cycles Algorithm2Regret::run(const InstanceTSP & instance){

    Solution2Cycles finalSolution;

    std::vector<bool > visited;

    visited.resize(instance.dimension, false);

    int cycleLength = 50;

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
                    break;
                }

                std::vector<std::pair<int, int > > insCosts;
                insCosts.resize(currentCycle->getLength());

                for(int insPos = 0; insPos < currentCycle->getLength(); insPos++){

                    int prev = (*currentCycle)[(currentCycle->getLength() + insPos - 1) % currentCycle->getLength()];
                    int succ = (*currentCycle)[insPos];
                    int diff = instance.matrix[prev][v] + instance.matrix[v][succ] - instance.matrix[prev][succ];

                    insCosts[v] = {v, diff};
                }

                std::sort(insCosts.begin(), insCosts.end(), [](const std::pair<int, int> & a, const std::pair<int, int> & b) -> bool{
                    return a.second < b.second;
                });

                int regret = insCosts[1].second - insCosts.front().second;
                if(regret > maxRegret){
                    maxRegret = regret;
                    pos = insCosts.front().first;
                    cost = insCosts.front().second;
                    next = v;
                } else if(regret == maxRegret){
                    
                    if(insCosts.front().second < cost){
                        maxRegret = regret;
                        pos = insCosts.front().first;
                        cost = insCosts.front().second;
                        next = v;
                    }
                }
            }

            currentCycle->addVertex(pos, next);
            visited[next]= true;
        }
    }

    finalSolution.setAlgorithmType("2-regret");
    finalSolution.setInstanceName(instance.getName());

    finalSolution.setInstance(instance);

    return finalSolution;
}