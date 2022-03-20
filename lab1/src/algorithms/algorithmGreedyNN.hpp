#ifndef ALGORITHM_GREEDY_NN_HPP
#define ALGORITHM_GREEDY_NN_HPP

#include "algorithm2cycles.hpp"

class AlgorithmGreedyNN : public Algorithm2cycles {

private:

    bool allVisited(std::vector<bool > &);

public:

    const std::string name = "greedy";

    AlgorithmGreedyNN(){}

    const Solution2Cycles run(const InstanceTSP &) override;
    const std::string getName() override{ return name;}
};

#endif