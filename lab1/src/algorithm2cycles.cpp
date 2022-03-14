#include "algorithm2cycles.hpp"

int findClosestVertex(int v, const InstanceTSP & instance, std::vector<bool > & visited){

    int min = RAND_MAX;
    int closestVertex;

    for(int i = 0; i < instance.dimension; i++){

        if(instance.matrix[v][i] < min){

            closestVertex = i;
        }
    }

    return closestVertex;
}