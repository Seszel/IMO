#ifndef CYCLE_HPP
#define CYCLE_HPP

<<<<<<< HEAD

=======
>>>>>>> 1886f2620aa0ebad19b2eea334a92f2c6774ab83
#include "instanceTSP.hpp"
#include <vector>
#include <string>

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

    const std::string cycleToJsonList(const InstanceTSP *);
};

#endif