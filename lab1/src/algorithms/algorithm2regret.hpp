#ifndef ALGORITHM_2_REGRET_HPP
#define ALGORITHM_2_REGRET_HPP

#include "algorithm2cycles.hpp"
#include "../instances/instanceTSP.hpp"
#include "../solutions/solution2Cycles.hpp"

#include <vector>
#include <algorithm>
#include <utility>

class Algorithm2Regret : public Algorithm2cycles{

private:

public:

    Algorithm2Regret(){}

    const Solution2Cycles run(const InstanceTSP &) override;
};

#endif