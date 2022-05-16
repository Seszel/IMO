#include "cycle.hpp"

const int Cycle::getTotalCost(){

    return this->totalCost;
}

int & Cycle::operator[](int index){

    if(index < 0 || index >= this->vertices.size()){
        //raise exception
    }

    return this->vertices[index];
}

void Cycle::addVertex(std::size_t pos, const int vertex){

    if(pos < 0 || pos > this->vertices.size()){

        //raise exception
    }

    int vs = this->vertices.size();

    int prev = vertices[(vs + pos - 1) % vs];
    int succ = vertices[pos % vs];

    int del_edges = this->instance->matrix[prev][succ];
    int ins_edges = this->instance->matrix[prev][vertex] + this->instance->matrix[vertex][succ];

    totalCost += (ins_edges - del_edges);

    if(pos == this->vertices.size()){

        this->vertices.push_back(vertex);
    } else {

        this->vertices.insert(this->vertices.begin() + pos, vertex);
    }
}

void Cycle::pushBackVertex(const int vertex){

    int vs = this->vertices.size();



    if(this->vertices.size() >= 1){

        int prev = vertices[vs - 1];
        int succ = vertices[0];

        int del_edges = 0;
        if(vs > 1)
            del_edges = (this->instance->matrix[prev][succ]);
        int ins_edges = (this->instance->matrix[prev][vertex] + this->instance->matrix[vertex][succ]);

        this->totalCost += (ins_edges - del_edges);
    }
    
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

void Cycle::swap2Edges(const int a, const int b){

    int s = this->vertices.size();

    int prev_e1, succ_e1, prev_e2, succ_e2;

    prev_e1 = vertices[a];
    prev_e2 = vertices[b];

    succ_e1 = vertices[(a + 1) % s];
    succ_e2 = vertices[(b + 1) % s];

    int n_of_swaps = (abs(a - b) + 1) /2;

    int ins_egdes, del_edges;

    ins_egdes = instance->matrix[prev_e1][prev_e2] + instance->matrix[succ_e2][succ_e1];
    del_edges = instance->matrix[prev_e1][succ_e1] + instance->matrix[prev_e2][succ_e2];

    this->totalCost += (ins_egdes - del_edges);

    for(int i = 0; i < n_of_swaps; i++){

        int am = (a + i + 1) % s;
        int bm = (s + b - i) % s;
        std::swap(this->vertices[am], this->vertices[bm]);
    }
}

void Cycle::swap2Vertices(const int a, const int b){

    int vs = this->vertices.size();

    int prev_a = vertices[(vs + a - 1) % vs];
    int succ_a = vertices[(vs + a + 1) % vs];
    int prev_b = vertices[(vs + b - 1) % vs];
    int succ_b = vertices[(vs + b + 1) % vs];
    int _a = vertices[a];
    int _b = vertices[b];

    int del_edges = instance->matrix[prev_a][_a] + instance->matrix[_a][succ_a] +
                    instance->matrix[prev_b][_b] + instance->matrix[_b][succ_b];
    int ins_edges = instance->matrix[prev_a][_b] + instance->matrix[_a][succ_b];

    if(b - a == 1){

        ins_edges = instance->matrix[prev_a][_b] + instance->matrix[_a][succ_b] + 
                    instance->matrix[_a][_b] * 2;
    }
    else if(a == 0 && b == vs - 1){

        ins_edges = instance->matrix[prev_b][_a] + instance->matrix[_b][succ_a] +
                    instance->matrix[_a][_b] * 2;
    }
    else {

        ins_edges += (instance->matrix[_b][succ_a] + instance->matrix[prev_b][_a]);
    }

    totalCost += (ins_edges - del_edges);

    std::swap(this->vertices[a], this->vertices[b]);
}

int Cycle::calculateCostFromZero(){

    int sum = 0;

    for(int i = 0; i < vertices.size(); i++){

        sum += instance->matrix[vertices[i]][vertices[(i + 1) % vertices.size()]];
    }

    this->totalCost = sum;

    return sum;
}

const std::vector<int > Cycle::getCycleVertices(){

    return this->vertices;
}

void Cycle::removeVertex(std::size_t pos){

    int vertex = this->vertices[pos];
    int vs = this->vertices.size();

    int prev = vertices[(vs + pos - 1) % vs];
    int succ = vertices[(pos + 1) % vs];

    int ins_edges = this->instance->matrix[prev][succ];
    int del_edges = this->instance->matrix[prev][vertex] + this->instance->matrix[vertex][succ];

    totalCost += (ins_edges - del_edges);

    vertices.erase(vertices.begin() + pos);
}