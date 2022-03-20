#ifndef SOLUTION_2_CYCLES_HPP
#define SOLUTION_2_CYCLES_HPP

#include "solution.hpp"
#include "../cycle.hpp"
#include "../instances/instanceTSP.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <exception>

class Solution2Cycles : public Solution {

private:

    std::string instanceName;
    std::string algorithmType;
    std::vector<Cycle > cycles;
    std::vector<int> cycleLengths;

    const InstanceTSP * instance = nullptr;

public:

    Solution2Cycles(){}
    const int getTotalCost();
    void setInstanceName(const std::string);
    void setAlgorithmType(const std::string);
    const std::string getInstanceName();
    const std::string getAlgorithmType();
    void setInstance(const InstanceTSP &);

    Cycle * addCycle();

    Cycle operator[](std::size_t);
    bool operator<=(Solution2Cycles &);
    bool operator>=(Solution2Cycles &);

    const std::string saveAsJson();
};

#endif