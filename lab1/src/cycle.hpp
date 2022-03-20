#ifndef CYCLE_HPP
#define CYCLE_HPP


#include "instanceTSP.hpp"
#include <vector>
#include <string>

class Cycle{

private:

    std::vector<int > vertices;
    int totalCost;

public:

    Cycle(){}

    const int getTotalCost();
    int operator[](std::size_t);
    void removeVertex(std::size_t);
    void addVertex(std::size_t, const int);

    void pushBackVertex(const int);
    int getLength();

    const std::string cycleToJsonList(const InstanceTSP *);
};

#endif