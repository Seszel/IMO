#ifndef SOLUTION_2_CYCLES_HPP
#define SOLUTION_2_CYCLES_HPP

#include "solution.hpp"
#include "cycle.hpp"
#include "instanceTSP.hpp"
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

<<<<<<< HEAD
    const InstanceTSP * instance;
=======
    const InstanceTSP * instance = nullptr;
>>>>>>> 1886f2620aa0ebad19b2eea334a92f2c6774ab83

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
<<<<<<< HEAD

    const std::string saveAsJson();
=======
    void setInstance(const InstanceTSP &);
>>>>>>> 1886f2620aa0ebad19b2eea334a92f2c6774ab83
};

#endif