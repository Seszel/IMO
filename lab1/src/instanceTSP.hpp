#ifndef INSTANCE_TSP_HPP
#define INSTANCE_TSP_HPP

#include "instance.hpp"

#include <vector>
#include <iostream>

template <typename T>
struct Point{
    T x;
    T y;
};

class InstanceTSP : public Instance {

    private:
        std::string name;
        std::string type;
        std::string comment;
        int dimension;
        std::string edgeWeightType;
        std::vector<Point<int > > nodes;
        int ** matrix = nullptr;
    
    public:
        InstanceTSP(){

        }
        virtual ~InstanceTSP(){

            if(matrix != nullptr){
                delete matrix;
            }
        }

        void readFromFile(std::string path) override;
        void writeData() override;

};

#endif