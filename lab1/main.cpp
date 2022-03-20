#include "instanceTSP.hpp"

#include <iostream>

int main(int argc, char ** argv){
    InstanceTSP instance;
    instance.readFromFile("../data/kroa100.tsp");

    std::cout << "Data loaded" << std::endl;

    return 0;
}