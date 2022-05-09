#ifndef ALGORITHM_2_CYCLES_HPP
#define ALGORITHM_2_CYCLES_HPP

#include "../instances/instanceTSP.hpp"
#include "../solutions/solution2Cycles.hpp"
#include "algorithm.hpp"
#include <algorithm>
#include <vector>

struct Move {
    int a; // index of vertice in cycle
    int b; // index of vertice in cycle
    int cyc_num;
    int type;
    int a_v; // vertice number, corresponds to index 'a'
    int b_v; // vertice number, corresponds to index 'b'
    int as_v; // used only when swapping edges
    int bs_v; // used only when swapping edges
};

class Algorithm2cycles : public Algorithm {

private:


public:

    Algorithm2cycles(){}

    virtual ~Algorithm2cycles(){}

    virtual const Solution2Cycles run(const InstanceTSP &) = 0;
    virtual const std::string getName() = 0;

    int findClosestVertex(int, const InstanceTSP &, std::vector<bool > &);
    std::vector<Move> getMoves(Solution2Cycles &, std::vector<int>);
    const int calculateCostAfterMove(Solution2Cycles &, const Move);
};

#endif