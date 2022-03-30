#include "algorithmLocalGreedy.hpp"

const Solution2Cycles AlgorithmLocalGreedy::run(const InstanceTSP &){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startingSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startingSolution);

    bool improvementFound = true;

    while(improvementFound){

        improvementFound = false;

        // get available moves
        auto moves = this->getMoves(currentSolution, {
            Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_2_VERTICES, Solution2Cycles::SWAP_BETWEEN_CYCLES
        });

        // shuffle moves to obtain random sequence
        std::random_shuffle(moves.begin(), moves.end());

        // look for the first better move
        for(auto & move : moves){

            auto before_move_cost = currentSolution.getTotalCost();
            
            if(move.type == Solution2Cycles::SWAP_2_EDGES){

                currentSolution.swap2Edges(
                    move.a,
                    move.b,
                    &currentSolution[move.cyc_num]
                );
                
                if(before_move_cost > currentSolution.getTotalCost()){

                    improvementFound = true;
                    break;
                }
                else {
                    currentSolution.swap2Edges(
                        move.a,
                        move.b,
                        &currentSolution[move.cyc_num]
                    );
                }
            }
            else if(move.type == Solution2Cycles::SWAP_2_VERTICES){

                currentSolution.swap2VerticesInCycle(
                    move.a,
                    move.b,
                    &currentSolution[move.cyc_num]
                );

                if(before_move_cost > currentSolution.getTotalCost()){
                    
                    improvementFound = true;
                    break;
                }
                else {
                    currentSolution.swap2VerticesInCycle(
                        move.a,
                        move.b,
                        &currentSolution[move.cyc_num]
                    );
                }
            }
            else if(move.type == Solution2Cycles::SWAP_BETWEEN_CYCLES){

                currentSolution.swapVerticesBetweenCycles(
                    move.a,
                    move.b
                );

                if(before_move_cost > currentSolution.getTotalCost()){

                    improvementFound = true;
                    break;
                }
                else {
                    currentSolution.swapVerticesBetweenCycles(
                        move.a,
                        move.b
                    );
                }
            }
        }
    }

    return currentSolution;
}