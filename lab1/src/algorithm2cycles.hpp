#ifndef ALGORITHM_2_CYCLES_HPP
#define ALGORITHM_2_CYCLES_HPP

#include "algorithm.hpp"

class Algorithm2cycles : public Algorithm {

private:


public:

    Algorithm2cycles(){}

    virtual ~Algorithm2cycles(){}

    virtual const Solution & run(const Instance &) = 0;

};

#endif