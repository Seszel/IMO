#include "instanceTSP.hpp"

int main(int argc, char ** argv){
    InstanceTSP instance;
    instance.readFromFile("../data/kroa100.tsp");

    return 0;
}