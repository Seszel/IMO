#include "algorithmSeparateCycles.hpp"

const Solution2Cycles AlgorithmSeparateCycles::run(const InstanceTSP & instance){

    AlgorithmRandom algRandom;

    auto solution = algRandom.run(instance);

    Point<float> m1, m2;

    auto lenc1 = solution[0].getLength();
    auto lenc2 = solution[1].getLength();

    m1 = calculateMiddlePointOfCycle(0, &instance, solution);
    m2 = calculateMiddlePointOfCycle(1, &instance, solution);

    int distance = (m1.x - m2.x) * (m1.x - m2.x) + (m1.y - m2.y) * (m1.y - m2.y);

    bool improvementFound = true;

    while(improvementFound){

        improvementFound = false;

        auto moves = this->getMoves(solution, {Solution2Cycles::SWAP_BETWEEN_CYCLES});
        int min = 1e9;
        Move best_move;

        for(auto & move : moves){

            //calculate distance
            solution.swapVerticesBetweenCycles(move.a, move.b);

            m1 = calculateMiddlePointOfCycle(0, &instance, solution);
            m2 = calculateMiddlePointOfCycle(1, &instance, solution);

            solution.swapVerticesBetweenCycles(move.a, move.b);

            int d = (m1.x - m2.x) * (m1.x - m2.x) + (m1.y - m2.y) * (m1.y - m2.y);

            if(d > distance){

                distance = d;
                best_move = move;

                improvementFound = true;
            }
        }

        if(improvementFound){

            solution.swapVerticesBetweenCycles(best_move.a, best_move.b);
        }
    }

    solution.setAlgorithmType("separate_cycles");

    return solution;
}

Point<float> AlgorithmSeparateCycles::calculateMiddlePointOfCycle(const int cyc_num, const InstanceTSP * instance, Solution2Cycles solution){

    Point<float> res = {0, 0};
    int lenc = solution[cyc_num].getLength();

    for(int i = 0; i < lenc; i++){

        auto v = instance->nodes[solution[cyc_num][i]];
        res.x += v.x;
        res.y += v.y;
    }

    return {res.x / lenc, res.y / lenc};
}