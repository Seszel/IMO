#include "algorithmGreedyNN.hpp"

const Solution2Cycles AlgorithmGreedyNN::run(const InstanceTSP & instance){

    Solution2Cycles finalSolution;

    std::vector<bool > visited;

    visited.resize(instance.dimension, false);

    int cycleLength = instance.dimension/2;
    

    while(!allVisited(visited)){  

        //choose random starting vertex
        bool firstVertex = false;
        int randomStart = rand() % instance.dimension;
        while(visited[randomStart] == true)
            randomStart = rand() % instance.dimension; 

        int prevAddedVertex = randomStart;
        int nextVertex;

        finalSolution.setInstance(instance);

        Cycle * currentCycle = finalSolution.addCycle();

        currentCycle->pushBackVertex(randomStart);
        visited[randomStart] = true;


        while(currentCycle->getLength() < cycleLength){

            nextVertex = this->findClosestVertex(prevAddedVertex, instance, visited);
            visited[nextVertex] = true;
        
            currentCycle->pushBackVertex(nextVertex);
            prevAddedVertex = nextVertex;       
        }

        // currentCycle->pushBackVertex(randomStart); DODAWAC TEN WIERZCHOLEK, CZY NIE. CZY W LICZENIU KOSZTU JEST UWZGLEDNIANA KRAWEDZ OSTATNI DO PIERWSZEGO?
        firstVertex = false;
    }



    finalSolution.setAlgorithmType("greedy_nearest_neighbour");
    finalSolution.setInstanceName(instance.getName());

    return finalSolution;
}

bool AlgorithmGreedyNN::allVisited(std::vector<bool > & visited){

    for(auto i : visited)
        if(i == false)
            return false;

    return true;
}