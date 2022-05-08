#include "algorithmLocalCandidates.hpp"

std::vector<std::pair<int, std::vector<std::pair<int, int> > > > AlgorithmLocalCandidates::findKClosestVertices(int k, const InstanceTSP & instance, std::vector<Cycle > & cycles) {


    int min = RAND_MAX;
    std::vector<std::pair<int, std::vector<std::pair<int, int> > > > closestVertices;
    std::vector<int > temp(instance.dimension);
    std::vector<int > vertices0 = cycles[0].getCycleVertices();
    std::vector<int > vertices1 = cycles[1].getCycleVertices();

    for (int v=0; v<instance.dimension; v++){
        std::iota(temp.begin(), temp.end(),0);

        std::sort(temp.begin(), temp.end(), [&](int a, int b){
            return instance.matrix[v][a] < instance.matrix[v][b];
        });

        std::vector<std::pair<int, int> > temp_pair;

        for (int i=0; i<temp.size(); i++){
            int vertex = temp.at(i);
            if (std::find(vertices0.begin(), vertices0.begin() + k, vertex) != vertices0.begin() + k) {
                temp_pair.push_back(std::make_pair(0, vertex));
            } else if (std::find(vertices1.begin(), vertices1.begin() + k, vertex) != vertices1.begin() + k) {
                temp_pair.push_back(std::make_pair(1, vertex));
            }  
        }
        if (std::find(vertices1.begin(), vertices1.begin() + k, v) != vertices1.begin() + k) {
            closestVertices.push_back(std::make_pair(1, temp_pair));
        } else {
            closestVertices.push_back(std::make_pair(0, temp_pair));
        }
        
    }

    return closestVertices;
}

const Solution2Cycles AlgorithmLocalCandidates::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startSolution);

    auto cycles = currentSolution.getCycles();
    auto closestVertices = findKClosestVertices(10, instance, cycles);

    for (int vertex=0 ; vertex<closestVertices.size(); vertex++){
        std::vector<Move > moves;
        for (int pair=0; pair<closestVertices.size(); pair++) {
            if (closestVertices.at(vertex).first == closestVertices.at(vertex).second[pair].first) {
                Cycle cycle = cycles[closestVertices.at(vertex).first];
                moves.push_back({
                    vertex, closestVertices.at(vertex).second[pair].second,
                    closestVertices.at(vertex).first, Solution2Cycles::SWAP_2_EDGES
                });
            }
        }

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

void AlgorithmLocalCandidates::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

    