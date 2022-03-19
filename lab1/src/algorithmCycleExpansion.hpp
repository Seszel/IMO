#ifndef ALGORITHM_CYCLE_EXPANSION_HPP
#define ALGORITHM_CYCLE_EXPANSION_HPP

#include "algorithm2cycles.hpp"

class AlgorithmCycleExpansion : public Algorithm2cycles {

private:

    bool allVisited(std::vector<bool > &);

public:

    AlgorithmCycleExpansion(){}
    const Solution2Cycles run(const InstanceTSP &) override;
};

#endif