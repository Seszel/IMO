#include "algorithmCycleExpansion.hpp"

const Solution2Cycles AlgorithmCycleExpansion::run(const InstanceTSP & instance){

    Solution2Cycles finalSolution;

    std::vector<bool > visited;

    visited.resize(instance.dimension, false);

    int cycleLength = instance.dimension/2;

    finalSolution.setInstance(instance);

    struct Insertion{
        int v;
        int pos;
        int cost;
    };

    std::vector<Insertion> insertions = {};

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
        int cnt =0;
        //for each cycle
        while(currentCycle->getLength() < cycleLength){

            int min = std::numeric_limits<int>::max();
            int pos;
            int next;

            insertions.clear();
            insertions.shrink_to_fit();
            insertions.push_back({next, pos, min});

            for(int insPos = 0; insPos < currentCycle->getLength(); insPos++){

                for(int v = 0; v < instance.dimension; v++){

                    if(visited[v] == false){

                        int prev = (*currentCycle)[(currentCycle->getLength() + insPos - 1) % currentCycle->getLength()];
                        int succ = (*currentCycle)[insPos];
                        int diff = instance.matrix[prev][v] + instance.matrix[v][succ] - instance.matrix[prev][succ];

                        if(diff < insertions.back().cost){

                            if(insertions.size() == this->random_upper_bound){
                                insertions.pop_back();
                            }
                            insertions.push_back({v, insPos, diff});
                            std::sort(insertions.begin(), insertions.end(), [](const Insertion & a, const Insertion & b){
                                return a.cost < b.cost;
                            });
                        }
                    }
                }
            }

            int v = 0;
            if(cnt % this->freq == 0 && this->random_upper_bound > 1){
                int r = rand()%this->random_upper_bound;
                currentCycle->addVertex(insertions[r].pos, insertions[r].v);
                v = insertions[r].v;
            }
            else {
                v = insertions.front().v;
                currentCycle->addVertex(insertions.front().pos, insertions.front().v);
            }
            visited[v]= true;
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

const Solution2Cycles AlgorithmCycleExpansion::run1cycle(const InstanceTSP & instance){

    Solution2Cycles finalSolution;

    std::vector<bool > visited;

    visited.resize(instance.dimension, false);

    int cycleLength = instance.dimension;

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

    finalSolution.setAlgorithmType("cycle_expansion_1_cycle");
    finalSolution.setInstanceName(instance.getName());

    return finalSolution;
}