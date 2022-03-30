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

    std::vector<Move> moves;

    for(auto type : availableTypes){

        if(type == Solution2Cycles::SWAP_2_VERTICES){

            for(int cn = 0; cn < 2; cn++){
                for(int a = 0; a < currentSolution[cn].getLength() - 1; a++){
                    for(int b = a + 1; b < currentSolution[cn].getLength(); b++){
                        moves.push_back({
                            a,b,cn,type
                        });
                    }
                }
            }
        }
        else if(type == Solution2Cycles::SWAP_BETWEEN_CYCLES){

            for(int a = 0; a < currentSolution[0].getLength(); a++){
                for(int b = 0; b < currentSolution[1].getLength(); b++){
                    moves.push_back({
                        a,b,0,type
                    });                    
                }
            }
        }
        else if(type == Solution2Cycles::SWAP_2_EDGES){

            for(int cn = 0; cn < 2; cn++){
                for(int a = 0; a < currentSolution[cn].getLength() - 1; a++){
                    for(int b = a + 1; b < currentSolution[cn].getLength(); b++){
                        moves.push_back({
                            a,b,cn,type
                        });
                    }
                }
            }
        }
    }

    return moves;
}