#ifndef CYCLE_HPP
#define CYCLE_HPP

#include "instanceTSP.hpp"
#include <vector>

class Cycle{

private:

    std::vector<int > vertices;
    int totalCost;

public:

    Cycle(){
        this->totalCost = 0;
    }

    const int getTotalCost(const InstanceTSP &);
    int operator[](std::size_t);
    void removeVertex(std::size_t);
    void addVertex(std::size_t, const int);

    void pushBackVertex(const int);
    int getLength();
};

#endif