#ifndef SOLUTION_2_CYCLES_HPP
#define SOLUTION_2_CYCLES_HPP

#include "solution.hpp"
#include "../cycle.hpp"
#include "../instances/instanceTSP.hpp"
#include "../../lib/json/single_include/nlohmann/json.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <exception>

using namespace nlohmann;


class Solution2Cycles : public Solution {

private:

    std::string instanceName;
    std::string algorithmType;
    std::vector<Cycle > cycles;
    std::vector<int> cycleLengths;

    const InstanceTSP * instance = nullptr;

public:

    static const int SWAP_2_EDGES = 0;
    static const int SWAP_2_VERTICES = 1;
    static const int SWAP_BETWEEN_CYCLES = 2;

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

    void swapVerticesBetweenCycles(const int, const int);
    void swap2Edges(const int, const int, Cycle *);
    void swap2VerticesInCycle(const int, const int, Cycle *);

    const std::string saveAsJson();
};

#endif