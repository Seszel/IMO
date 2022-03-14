#include "solution2Cycles.hpp"

const int Solution2Cycles::getTotalCost(){

    int sum = 0;
    for(auto i : this->cycleLengths)
        sum += i;

    return sum;
}

void Solution2Cycles::setInstanceName(const std::string name){

    this->instanceName = name;
}
void Solution2Cycles::setAlgorithmType(const std::string algorithm){

    this->algorithmType = algorithm;
}
const std::string Solution2Cycles::getInstanceName(){

    return this->instanceName;
}
const std::string Solution2Cycles::getAlgorithmType(){

    return this->algorithmType;
}

Cycle Solution2Cycles::operator[](std::size_t index){

    if(index < 0 || index >= this->cycles.size()){

        // throw std::out_of_range("");
    }

    return this->cycles[index];
}

Cycle Solution2Cycles::addCycle(){

    this->cycles.push_back(Cycle());
    return this->cycles.back();
}

bool Solution2Cycles::operator<=(Solution2Cycles & s2c){

    return this->getTotalCost() <= s2c.getTotalCost();
}

bool Solution2Cycles::operator>=(Solution2Cycles & s2c){

    return this->getTotalCost() >= s2c.getTotalCost();
}