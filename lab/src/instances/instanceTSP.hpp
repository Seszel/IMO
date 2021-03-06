#ifndef INSTANCE_TSP_HPP
#define INSTANCE_TSP_HPP

#include "instance.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <limits>

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
        
    public:

        int dimension;
        std::string edgeWeightType;
        std::vector<Point<int > > nodes;
        std::vector<std::vector<int > > matrix;
        
        InstanceTSP(){

        }
        virtual ~InstanceTSP(){

            // if(matrix != nullptr){
            //     delete matrix;
            // }
        }

        void readFromFile(std::string path) override;
        void writeData() override;
        const std::string getName() const;

};

#endif