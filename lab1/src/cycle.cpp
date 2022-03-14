#include "cycle.hpp"

const int Cycle::getTotalCost(){

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