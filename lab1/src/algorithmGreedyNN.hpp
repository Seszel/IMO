#ifndef ALGORITHM_GREEDY_NN_HPP
#define ALGORITHM_GREEDY_NN_HPP

#include "algorithm2cycles.hpp"

class AlgorithmGreedyNN : public Algorithm2cycles {

private:

public:

    AlgorithmGreedyNN(){}

    virtual ~AlgorithmGreedyNN(){}

    const Solution2Cycles run(const InstanceTSP &) override;

    void generateCycles (const Instance &);
};

#endif