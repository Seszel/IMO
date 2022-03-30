#ifndef ALGORITHM_2_CYCLES_HPP
#define ALGORITHM_2_CYCLES_HPP

#include "../instances/instanceTSP.hpp"
#include "../solutions/solution2Cycles.hpp"
#include "algorithm.hpp"
#include <algorithm>
#include <vector>

struct Move {
    int a;
    int b;
    int cyc_num;
    int type;
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
};

#endif