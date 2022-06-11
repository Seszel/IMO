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

    float alpha = 1.f;
    float beta = 1.f;

public:

    const std::string name = "2regret";

    Algorithm2Regret(){}

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override{ return name;}
    void setParams(const float a, const float b);
};

#endif