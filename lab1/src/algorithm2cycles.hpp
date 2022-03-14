#ifndef ALGORITHM_2_CYCLES_HPP
#define ALGORITHM_2_CYCLES_HPP

#include "instanceTSP.hpp"
#include "solution2Cycles.hpp"
#include "algorithm.hpp"
#include <algorithm>
#include <vector>


class Algorithm2cycles : public Algorithm {

private:


public:

    Algorithm2cycles(){}

    virtual ~Algorithm2cycles(){}

    virtual const Solution2Cycles run(const InstanceTSP &) = 0;

    int findClosestVertex(int, const InstanceTSP &, std::vector<bool > &);
};

#endif