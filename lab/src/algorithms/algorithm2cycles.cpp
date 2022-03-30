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

const int Algorithm2cycles::calculateCostAfterMove(Solution2Cycles & currentSolution, const Move move){

    int value = 0;

    if(move.type == Solution2Cycles::SWAP_2_EDGES){

        currentSolution.swap2Edges(
            move.a,
            move.b,
            &currentSolution[move.cyc_num]
        );

        value = currentSolution.getTotalCost();

        currentSolution.swap2Edges(
            move.a,
            move.b,
            &currentSolution[move.cyc_num]
        );
    }
    else if(move.type == Solution2Cycles::SWAP_2_VERTICES){

        currentSolution.swap2VerticesInCycle(
            move.a,
            move.b,
            &currentSolution[move.cyc_num]
        );

        value = currentSolution.getTotalCost();

        currentSolution.swap2VerticesInCycle(
            move.a,
            move.b,
            &currentSolution[move.cyc_num]
        );

    }
    else if(move.type == Solution2Cycles::SWAP_BETWEEN_CYCLES){

        currentSolution.swapVerticesBetweenCycles(
            move.a,
            move.b
        );

        value = currentSolution.getTotalCost();

        currentSolution.swapVerticesBetweenCycles(
            move.a,
            move.b
        );
    }

    return value;
}