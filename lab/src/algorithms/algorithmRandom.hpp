#ifndef ALGORITHM_RANDOM_HPP
#define ALGORITHM_RANDOM_HPP

#include "algorithm2cycles.hpp"
#include "../allinstances.hpp"
#include "../allsolutions.hpp"

#include <vector>
#include <algorithm>

class AlgorithmRandom : public Algorithm2cycles {

private:


public:

    AlgorithmRandom(){}

    virtual ~AlgorithmRandom(){}

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override;
};

#endif