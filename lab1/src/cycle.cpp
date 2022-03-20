#include "cycle.hpp"

const int Cycle::getTotalCost(const InstanceTSP & instance){

    int cost = 0;

    for(int i = 0; i < this->vertices.size(); i ++){

        int prev = this->vertices[i];
        int succ = this->vertices[(i + 1 + this->vertices.size()) % this->vertices.size()];

        cost +=  instance.matrix[prev][succ];
    }

    this->totalCost = cost;

    return this->totalCost;
}

int Cycle::operator[](std::size_t index){

    if(index < 0 || index >= this->vertices.size()){
        //raise exception
    }

    return this->vertices[index];
}

void Cycle::addVertex(std::size_t pos, const int vertex){

    if(pos < 0 || pos > this->vertices.size()){

        //raise exception
    }

    if(pos == this->vertices.size()){

        this->vertices.push_back(vertex);
    } else {

        this->vertices.insert(this->vertices.begin() + pos, vertex);
    }
}

void Cycle::pushBackVertex(const int vertex){

    this->vertices.push_back(vertex);
}

int Cycle::getLength(){

    return this->vertices.size();
}

const std::string Cycle::cycleToJsonList(const InstanceTSP * instance){

    std::string out = "";
    out += "[";

    for(int i = 0; i < this->getLength(); i++){

        int prev = i;        
        int succ = (i + 1) % this->getLength();

        out += "[" + std::to_string(this->vertices[prev]) + ", " + 
            std::to_string(this->vertices[succ]) + ", " + std::to_string(instance->matrix[prev][succ]) + "]";

        if(i < this->getLength() - 1){
            out += ", ";
        }
    }

    out += "]";

    return out;
}