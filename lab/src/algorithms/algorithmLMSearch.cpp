#include "algorithmLMSearch.hpp"

const Solution2Cycles AlgorithmLMSearch::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    auto moves = this->getMoves(currentSolution, this->availableMoveTypes);

    std::unordered_map<std::size_t, std::pair<Move, int> > LM = {};
    for(auto & move : moves){
        int delta = calculateCostAfterMove(currentSolution, move) - currentSolution.getTotalCost();
        // add only moves that improve solution
        // if(delta < currentSolution.getTotalCost()){
            LM[getHashOfMove(move)] = {move, delta};            
        // }
    }

    auto t = LM.size();
    int tt;

    bool foundMove = true;

    while(foundMove){
        foundMove = false;

        // sort moves from LM
        std::vector<std::pair<Move, int> > sorted_moves = {};
        for(const auto &m : LM){
            if(m.second.second < 0){
                sorted_moves.push_back(m.second);                
            }
        }
        std::sort(sorted_moves.begin(), sorted_moves.end(), [](std::pair<Move, int> a, std::pair<Move, int> b){
            return a.second < b.second;
        });

        for(auto move : sorted_moves){
            if(foundMove == true){
                break;
            }
            switch (isApplicable(currentSolution, move.first))
            {
            case APPLICABLE:
                // apply move
                foundMove = true;
                currentSolution.makeMove(
                    move.first.type, move.first.a, move.first.b, &currentSolution[move.first.cyc_num]
                );
                // update LM, add new moves
                updateLM(LM, move.first, currentSolution);
                break;
            case NOT_APPLICABLE:
                // remove from LM
                LM.erase(getHashOfMove(move.first));
                break;
            default:
                // move can be applicable in the future
                break;
            }
        }
    }

    bestSolution = currentSolution;
    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void AlgorithmLMSearch::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void AlgorithmLMSearch::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}

void AlgorithmLMSearch::updateLM(std::unordered_map<size_t, std::pair<Move, int> > &LM, Move move, Solution2Cycles &sol){

    int a = move.a;
    int b = move.b;
    int as = (a + 1) % 100;
    int bs = (b + 1) % 100;
    int ap = (a + 99) % 100;
    int bp = (b + 99) % 100;
    int cyc_num = move.cyc_num;
    int type = move.type;
    Move m;
    int cost = sol.getTotalCost();
    //swap two edges
    for(int i = 0; i < sol[cyc_num].getLength(); i++){
        m = {a, i, cyc_num, Solution2Cycles::SWAP_2_EDGES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
        m = {i, b, cyc_num, Solution2Cycles::SWAP_2_EDGES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
        m = {as, i, cyc_num, Solution2Cycles::SWAP_2_EDGES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
        m = {i, bs, cyc_num, Solution2Cycles::SWAP_2_EDGES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
    }
    //swap vertices between cycles
    for(int i = 0; i < sol[0].getLength(); i ++){
        m = {a, i, cyc_num, Solution2Cycles::SWAP_BETWEEN_CYCLES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
        m = {i, b, cyc_num, Solution2Cycles::SWAP_BETWEEN_CYCLES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }

        m = {as, i, cyc_num, Solution2Cycles::SWAP_BETWEEN_CYCLES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
        m = {i, bs, cyc_num, Solution2Cycles::SWAP_BETWEEN_CYCLES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
        m = {ap, i, cyc_num, Solution2Cycles::SWAP_BETWEEN_CYCLES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
        m = {i, bp, cyc_num, Solution2Cycles::SWAP_BETWEEN_CYCLES};
        if(LM.find(getHashOfMove(m)) != LM.end()){
            LM[getHashOfMove(m)].second = calculateCostAfterMove(sol, m) - cost;
        }
    }
}