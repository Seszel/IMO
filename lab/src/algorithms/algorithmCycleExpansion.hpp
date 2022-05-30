#ifndef ALGORITHM_CYCLE_EXPANSION_HPP
#define ALGORITHM_CYCLE_EXPANSION_HPP

#include "algorithm2cycles.hpp"

class AlgorithmCycleExpansion : public Algorithm2cycles {

private:

    bool allVisited(std::vector<bool > &);

public:

    const std::string name = "cycle_expansion";

    AlgorithmCycleExpansion(){}
    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override{ return name;}
    const Solution2Cycles run1cycle(const InstanceTSP &);
};

#endif