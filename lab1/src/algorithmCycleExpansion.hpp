#ifndef ALGORITHM_CYCLE_EXPANSION_HPP
#define ALGORITHM_CYCLE_EXPANSION_HPP

#include "algorithm2cycles.hpp"
#include "solution2Cycles.hpp"
#include "instanceTSP.hpp"

class AlgorithmCycleExpansion : public Algorithm2cycles {

private:

public:

    AlgorithmCycleExpansion(){}
    const Solution2Cycles run(const InstanceTSP &) override;
};

#endif