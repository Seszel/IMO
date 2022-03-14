#ifndef CYCLE_HPP
#define CYCLE_HPP

#include <vector>

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

};

#endif