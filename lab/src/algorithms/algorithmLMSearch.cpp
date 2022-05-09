#include "algorithmLMSearch.hpp"

const Solution2Cycles AlgorithmLMSearch::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    auto moves = this->getMoves(currentSolution, this->availableMoveTypes);

    std::unordered_map<std::size_t, std::pair<Move, int> > LM = {};
    for(auto & move : moves){
        int delta = calculateCostAfterMove(currentSolution, move);
        // add only moves that improve solution
        if(delta < 0){
            LM[getHashOfMove(move)] = {move, calculateCostAfterMove(currentSolution, move)};            
        }
    }

    bool foundMove = true;

    while(foundMove){
        foundMove = false;

        // sort moves
        std::vector<std::pair<Move, int> > sorted_moves = {};
        for(const auto &m : LM){
            sorted_moves.push_back(m.second);
        }
        std::sort(sorted_moves.begin(), sorted_moves.end(), [](std::pair<Move, int> a, std::pair<Move, int> b){
            return a.second < b.second;
        });

        for(auto move : sorted_moves){
            switch (isApplicable(currentSolution, move))
            {
            case APPLICABLE:
                // apply move
                break;
            case NOT_APPLICABLE:
                // remove from LM
                

            default:
                break;
            }
        }
    }

    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void AlgorithmLMSearch::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmLMSearch::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}