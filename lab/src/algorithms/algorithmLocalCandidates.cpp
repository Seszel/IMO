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

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution);
    Solution2Cycles currentSolution = Solution2Cycles(*this->startSolution);

    auto cycles = currentSolution.getCycles();
    auto closestVertices = findKClosestForAll(k, instance, currentSolution);

    bool foundImprovement = true;

    while(foundImprovement){

        foundImprovement = false;        

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

                // if w and v belongs to difference cycles perform some heruistic swap
                // if(wcn != vcn) {
                //     for(int u_ind; u_ind < closestVertices[w].size(); u_ind ++){
                //         auto u = closestVertices[w][u_ind];
                //         if(u != v && )
                //     }
                // }
                if(vcn != wcn)
                    continue;

                delta += Algorithm2cycles::calculateCostAfterMove(currentSolution, {
                    w_ind, v_ind, vcn, Solution2Cycles::INSERT_EDGE
                });

                if(delta < 0){
                    foundImprovement = true;
                    currentSolution.moveVertice(w_ind, v_ind, &currentSolution[vcn]);

                    
                    if(val + delta != currentSolution.getTotalCost()){
                        std::cerr << "o nie";
                    }
                }
            }
        }        
    }

    return currentSolution;

}

void AlgorithmLocalCandidates::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

    