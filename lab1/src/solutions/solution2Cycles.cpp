#include "solution2Cycles.hpp"

const int Solution2Cycles::getTotalCost(){

    int sum = 0;
    for(int i = 0; i < this->cycles.size(); i ++)
        sum += this->cycles[i].getTotalCost(*this->instance);

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

Cycle * Solution2Cycles::addCycle(){

    this->cycles.push_back(Cycle());
    return &this->cycles.back();
}

bool Solution2Cycles::operator<=(Solution2Cycles & s2c){

    return this->getTotalCost() <= s2c.getTotalCost();
}

bool Solution2Cycles::operator>=(Solution2Cycles & s2c){

    return this->getTotalCost() >= s2c.getTotalCost();
}

const std::string Solution2Cycles::saveAsJson(){

    json data;
    data["type"] = this->algorithmType;
    data["instance"]["name"] = this->instanceName;
    std::vector<std::vector<int > > points;
    std::vector<std::vector<std::vector<int > > > edges;
    
    for(int j = 0; j < instance->dimension; j++){
        points.push_back({});
        points[j].push_back(instance->nodes[j].x);
        points[j].push_back(instance->nodes[j].y);
    }
    for(int i = 0; i < this->cycles.size(); i++){

        edges.push_back({});
        //for each cycle construct points and edges arrays
        int cycLen = this->cycles[i].getLength();
        for(int j = 0; j < cycLen; j++){
            edges[i].push_back({});

            int pred = this->cycles[i][j];
            int succ = this->cycles[i][(j + 1) % cycLen];

            edges[i][j].push_back(pred);
            edges[i][j].push_back(succ);
            edges[i][j].push_back(this->instance->matrix[pred][succ]);
        }
    } 

    for(int i = 0; i < this->cycles.size(); i++){

        data["instance"]["cycle"][i]["points"] = points;
        data["instance"]["cycle"][i]["edges"] = edges[i];
    }

    return data.dump();
}

void Solution2Cycles::setInstance(const InstanceTSP & instance){

    this->instance = &instance;
}

void swap2Edges(const int a, const int b, Cycle * cycle){

    cycle->swap2Edges(a, b);
}

void swap2VerticesInCycle(const int a, const int b, Cycle * cycle){

    cycle->swap2Vertices(a, b);
}