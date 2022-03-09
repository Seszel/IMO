#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <fstream>
#include <string>
class Instance {

    public:
        virtual void readFromFile(std::string path) = 0;
        virtual void writeData() = 0;
};

#endif

