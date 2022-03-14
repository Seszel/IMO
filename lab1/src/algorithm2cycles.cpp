#include "algorithm2cycles.hpp"

int findClosestVertex(int v, const InstanceTSP & instance, std::vector<bool > & visited){

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