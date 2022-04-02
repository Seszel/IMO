#ifndef ALGORITHM_SEPARATE_CYCLES
#define ALGORITHM_SEPARATE_CYCLES

#include "algorithm2cycles.hpp"
#include "../allalgorithms.hpp"
#include "../allsolutions.hpp"
#include "../allinstances.hpp"

class AlgorithmSeparateCycles : public Algorithm2cycles{

private:

    Point<float> calculateMiddlePointOfCycle(const int, const InstanceTSP *, Solution2Cycles);

public:

    AlgorithmSeparateCycles(){}

    virtual ~AlgorithmSeparateCycles(){}

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override { return "separate_cycles"; }
};

#endif