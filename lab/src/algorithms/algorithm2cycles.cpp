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
                            a,b,cn,type, currentSolution[cn][a], currentSolution[cn][b]
                        });
                    }
                }
            }
        }
        else if(type == Solution2Cycles::SWAP_BETWEEN_CYCLES){

            for(int a = 0; a < currentSolution[0].getLength(); a++){
                for(int b = 0; b < currentSolution[1].getLength(); b++){
                    moves.push_back({
                        a,b,0,type, currentSolution[0][a], currentSolution[1][b]
                    });                    
                }
            }
        }
        else if(type == Solution2Cycles::SWAP_2_EDGES){

            for(int cn = 0; cn < 2; cn++){
                for(int a = 0; a < currentSolution[cn].getLength() - 2; a++){
                    for(int b = a + 2; b < currentSolution[cn].getLength(); b++){
                        int as_v, bs_v;
                        as_v = currentSolution[cn][(a + 1) % currentSolution[cn].getLength()];
                        bs_v = currentSolution[cn][(b + 1) % currentSolution[cn].getLength()];
                        moves.push_back({
                            a,b,cn,type, currentSolution[cn][a], currentSolution[cn][b],
                            as_v, bs_v
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

const std::vector<std::pair<int, int> > Algorithm2cycles::findVertices(std::vector<int> & vertices, Solution2Cycles & sol){

    std::vector<std::pair<int, int> > tuples;//first cycle, second index
    for(auto & v : vertices){
        for(int j = 0; j < sol.getCycles().size(); j++){
            for(int i = 0; i < sol[j].getLength(); i ++){
                if(v == sol[j][i]){
                    tuples.push_back({j, i});
                }
            }
        }
    }

    if(tuples.size() != vertices.size()){
        std::cerr << "źle";
    }

    return tuples;
}
const std::vector<int> Algorithm2cycles::findKClosestVertices(const int v, const int k, const InstanceTSP & instance){

    std::vector<const int *> ptrs(instance.dimension);

    for(int i = 0; i < instance.dimension; i ++){
        ptrs[i] = &instance.matrix[v][i];
    }  

    std::sort(ptrs.begin(), ptrs.end(), [](const int * a, const int * b){
        return *a < *b;
    });

    int K = std::min(k, instance.dimension - 1);

    std::vector<int> out(K);
    for(int i = 0; i < K; i++){
        std::ptrdiff_t d = ptrs[i] - &instance.matrix[v][0];
        out[i] = d;
    }

    return out;
}