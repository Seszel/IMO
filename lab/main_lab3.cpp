#include "src/allinstances.hpp"
#include "src/allalgorithms.hpp"

#include <iostream>

int main(int argc, char ** argv){
    InstanceTSP instance;
    instance.readFromFile("data/kroa100.tsp");

    std::cout << "Data loaded lab 3" << std::endl;

    return 0;
}