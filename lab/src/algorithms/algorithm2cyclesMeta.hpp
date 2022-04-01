#ifndef ALGORITHM_2_CYCLES_META_HPP
#define ALGORITHM_2_CYCLES_META_HPP

#include "algorithm2cycles.hpp"

class Algorithm2cyclesMeta : public Algorithm2cycles {

public:

    virtual void setAvailableMoveTypes(std::vector<int>) = 0;
    virtual void setStartingSolution(const Solution2Cycles *) = 0;
};

#endif