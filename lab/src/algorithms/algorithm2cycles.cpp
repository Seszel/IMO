#include "algorithm2cycles.hpp"

int Algorithm2cycles::findClosestVertex(int v, const InstanceTSP & instance, std::vector<bool > & visited){

    int min = RAND_MAX;
    int closestVertex = -1;

    for(int i = 0; i < instance.dimension; i++){

        if(instance.matrix[v][i] < min && visited[i] == false){

            closestVertex = i;
            min = instance.matrix[v][i];
        }
    }

    return closestVertex;
}

std::vector<Move> Algorithm2cycles::getMoves(Solution2Cycles & currentSolution, std::vector<int> availableTypes){

    for(auto type : availableTypes){

        //TODO

        if(type == Solution2Cycles::SWAP_2_VERTICES){

        }
        else if(type == Solution2Cycles::SWAP_BETWEEN_CYCLES){


        }
        else if(type == Solution2Cycles::SWAP_2_EDGES){


        }
    }
}