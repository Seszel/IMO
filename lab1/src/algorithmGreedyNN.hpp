#ifndef ALGORITHM_GREEDY_NN_HPP
#define ALGORITHM_GREEDY_NN_HPP

#include "algorithm2cycles.hpp"

class AlgorithmGreedyNN : public Algorithm2cycles {

private:

public:

    AlgorithmGreedyNN(){}

    virtual ~AlgorithmGreedyNN(){}

    const Solution & run(const Instance &) override;

    void generateCycles (const Instance &);
};

#endif