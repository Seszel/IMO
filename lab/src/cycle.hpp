#ifndef CYCLE_HPP
#define CYCLE_HPP

#include "instances/instanceTSP.hpp"
#include <vector>
#include <string>

class Cycle{

private:

    std::vector<int > vertices;
    int totalCost;
    const InstanceTSP * instance = nullptr;

public:

    Cycle(const InstanceTSP & i){
        this->totalCost = 0;
        this->instance = &i;
    }

    const int getTotalCost();
    int & operator[](int);
    void removeVertex(std::size_t);
    void addVertex(std::size_t, const int);

    void pushBackVertex(const int);
    int getLength();

    const std::string cycleToJsonList(const InstanceTSP *);

    void swap2Edges(const int, const int);
    void swap2Vertices(const int, const int);

    int calculateCostFromZero();

    friend class Solution2Cycles;
};

#endif