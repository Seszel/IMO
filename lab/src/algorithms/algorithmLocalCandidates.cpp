#include "algorithmLocalCandidates.hpp"

std::vector<std::vector<int> > AlgorithmLocalCandidates::findKClosestForAll(int k, const InstanceTSP & instance, Solution2Cycles & sol) {

    int min = RAND_MAX;
    std::vector<std::vector<int> > closestVertices;

    for (int v=0; v<instance.dimension; v++){

        auto closest_vertices_v = this->findKClosestVertices(v, k, instance);
        // auto clos_indx = this->findVertices(closest_vertices_v, sol);

        closestVertices.push_back(closest_vertices_v);
    }

    return closestVertices;
}

const Solution2Cycles AlgorithmLocalCandidates::run(const InstanceTSP & instance){

    int swaps_cnt = 0, move_cnt = 0;


    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startSolution);

    auto cycles = currentSolution.getCycles();
    auto closestVertices = findKClosestForAll(k, instance, currentSolution);

    bool foundImprovement = true;

    while(foundImprovement){

        foundImprovement = false;        
        int min = RAND_MAX;
        Move best_move;

        
        for (int v = 0 ; v < closestVertices.size(); v++){

            std::vector<int> tmp = {v};
            auto v_indx = findVertices(tmp, currentSolution)[0];
            auto v_ind = v_indx.second;
            auto vcn = v_indx.first;
            auto clos_indx = this->findVertices(closestVertices[v], currentSolution);
            for(int w_ind = 0; w_ind < closestVertices[v].size(); w_ind ++){

                int w = closestVertices[v][w_ind];
                int wcn = clos_indx[w_ind].first;
                // calculate cost of inserting edge u <-> w to the current solution
                int val = currentSolution.getTotalCost();
                int delta = -currentSolution.getTotalCost(); 
                int a, b;
                // if w and v belongs to different cycles perform some heruistic swap
                if(wcn != vcn) {
                    a = (vcn == 0 ? v_ind : w_ind);
                    b = (vcn == 0 ? w_ind : v_ind);
                    delta += Algorithm2cycles::calculateCostAfterMove(currentSolution, {
                        a, b, 0, Solution2Cycles::SWAP_BETWEEN_CYCLES
                    });
                }
                else {
                    delta += Algorithm2cycles::calculateCostAfterMove(currentSolution, {
                        w_ind, v_ind, vcn, Solution2Cycles::INSERT_EDGE
                    });                    
                }

                if(delta < 0){
                    
                    foundImprovement = true;
                    if(wcn == vcn){
                        // if(delta < min){
                        //     min = delta;
                        //     best_move = {
                        //         w_ind, v_ind, vcn, Solution2Cycles::INSERT_EDGE
                        //     };
                        // }
                        currentSolution.moveVertice(w_ind, v_ind, &currentSolution[vcn]);
                        move_cnt ++;                        
                    }
                    else {
                        // if(delta < min){
                        //     min = delta;
                        //     best_move = {
                        //         a, b, 0, Solution2Cycles::SWAP_BETWEEN_CYCLES
                        //     };
                        // }
                        currentSolution.swapVerticesBetweenCycles(a, b);
                        swaps_cnt ++;
                    }


                    // if(val + delta != currentSolution.getTotalCost()){
                    //     std::cerr << "o nie";
                    // }
                }
            }
        } 

        // if(foundImprovement){
        //     if(best_move.type == Solution2Cycles::SWAP_BETWEEN_CYCLES){
        //         currentSolution.swapVerticesBetweenCycles(best_move.a, best_move.b);            
        //     }
        //     else {
        //         currentSolution.moveVertice(best_move.a, best_move.b, &currentSolution[best_move.cyc_num]);
        //     }
        // }       
    }
    std::cerr << "swaps: "<< swaps_cnt << " moves: " << move_cnt << std::endl;

    return currentSolution;

}

void AlgorithmLocalCandidates::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

    