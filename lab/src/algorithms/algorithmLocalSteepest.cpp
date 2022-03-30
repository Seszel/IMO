#include "algorithmLocalSteepest.hpp"

const Solution2Cycles AlgorithmLocalSteepest::run(const InstanceTSP &){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startSolution);

    bool improvementFound = true;

    while(improvementFound){

        improvementFound = false;

        // get available moves
        auto moves = this->getMoves(currentSolution, {
            Solution2Cycles::SWAP_2_EDGES, Solution2Cycles::SWAP_2_VERTICES, Solution2Cycles::SWAP_BETWEEN_CYCLES
        });

        // find best move that minimizes objective function
        Move best_move;
        int min_f_value = std::numeric_limits<int>::max();

        for(auto & move : moves){

            auto move_value = this->calculateCostAfterMove(currentSolution, move);

            if(move_value < min_f_value){
                min_f_value = move_value;
                best_move = move;
            }
        }

        if(min_f_value < currentSolution.getTotalCost()){

            improvementFound = true;
            currentSolution.makeMove(
                best_move.type,
                best_move.a,
                best_move.b,
                &currentSolution[best_move.cyc_num]
            );
        }
    }

    return currentSolution;
}