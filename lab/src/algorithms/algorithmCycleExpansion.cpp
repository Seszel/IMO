#include "algorithmCycleExpansion.hpp"

const Solution2Cycles AlgorithmCycleExpansion::run(const InstanceTSP & instance){

    Solution2Cycles finalSolution;

    std::vector<bool > visited;

    visited.resize(instance.dimension, false);

    int cycleLength = 50;

    finalSolution.setInstance(instance);

    while(!allVisited(visited)){

        //choose random starting vertex
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

            int min = std::numeric_limits<int>::max();
            int pos;
            int next;

            for(int insPos = 0; insPos < currentCycle->getLength(); insPos++){

                for(int v = 0; v < instance.dimension; v++){

                    if(visited[v] == false){

                        int prev = (*currentCycle)[(currentCycle->getLength() + insPos - 1) % currentCycle->getLength()];
                        int succ = (*currentCycle)[insPos];
                        int diff = instance.matrix[prev][v] + instance.matrix[v][succ] - instance.matrix[prev][succ];

                        if(diff < min){

                            min = diff;
                            next = v;
                            pos = insPos;
                        }
                    }
                }
            }

            currentCycle->addVertex(pos, next);
            visited[next]= true;
        }
    }

    finalSolution.setAlgorithmType("cycle_expansion");
    finalSolution.setInstanceName(instance.getName());

    return finalSolution;
}

bool AlgorithmCycleExpansion::allVisited(std::vector<bool > & visited){

    for(auto i : visited)
        if(i == false)
            return false;

    return true;
}