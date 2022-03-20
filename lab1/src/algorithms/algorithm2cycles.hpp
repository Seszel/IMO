#ifndef ALGORITHM_2_CYCLES_HPP
#define ALGORITHM_2_CYCLES_HPP

#include "../instances/instanceTSP.hpp"
#include "../solutions/solution2Cycles.hpp"
#include "algorithm.hpp"
#include <algorithm>
#include <vector>

class Algorithm2cycles : public Algorithm {

private:


public:

    Algorithm2cycles(){}

    virtual ~Algorithm2cycles(){}

    virtual const Solution2Cycles run(const InstanceTSP &) = 0;
    virtual const std::string getName() = 0;

    int findClosestVertex(int, const InstanceTSP &, std::vector<bool > &);
};

#endif