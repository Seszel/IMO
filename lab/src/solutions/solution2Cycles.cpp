#include "solution2Cycles.hpp"

const int Solution2Cycles::getTotalCost(){

    int sum = 0;
    for(int i = 0; i < this->cycles.size(); i ++)
        sum += this->cycleLengths[i];

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

Cycle & Solution2Cycles::operator[](std::size_t index){

    if(index < 0 || index >= this->cycles.size()){

        // throw std::out_of_range("");
    }

    return this->cycles[index];
}

Cycle * Solution2Cycles::addCycle(){

    this->cycles.push_back(Cycle(*this->instance));
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

void Solution2Cycles::swap2Edges(const int a, const int b, Cycle * cycle){

    cycle->swap2Edges(a, b);
}

void Solution2Cycles::swap2VerticesInCycle(const int a, const int b, Cycle * cycle){

    cycle->swap2Vertices(a, b);
}

void  Solution2Cycles::swapVerticesBetweenCycles(const int a, const int b){

    int del_edges_c0, del_edges_c1, ins_edges_c1, ins_edges_c0;
    int c0 = this->cycles[0].getLength();
    int c1 = this->cycles[1].getLength();

    int a_prev = cycles[0][(c0 + a - 1) % c0];
    int a_succ = cycles[0][(c0 + a + 1) % c0];
    int b_prev = cycles[1][(c1 + b - 1) % c1];
    int b_succ = cycles[1][(c1 + b + 1) % c1];

    del_edges_c0 = this->instance->matrix[a_prev][a] + this->instance->matrix[a][a_succ];
    del_edges_c1 = this->instance->matrix[b_prev][b] + this->instance->matrix[b][b_succ];

    ins_edges_c0 = this->instance->matrix[a_prev][b] + this->instance->matrix[b][a_succ];
    ins_edges_c1 = this->instance->matrix[b_prev][a] + this->instance->matrix[a][b_succ];

    auto tmp = this->cycles[0][a];
    this->cycles[0][a] = this->cycles[1][b];
    this->cycles[1][b] = tmp;

    this->cycles[0].totalCost += (ins_edges_c0 - del_edges_c0);
    this->cycles[1].totalCost += (ins_edges_c1 - del_edges_c1);
}

void Solution2Cycles::makeMove(const int type, const int a, const int b, Cycle * c){

    if(type == Solution2Cycles::SWAP_2_EDGES){

        this->swap2Edges(a, b, c);
    }
    else if(type == Solution2Cycles::SWAP_2_VERTICES){

        this->swap2VerticesInCycle(a, b, c);
    }
    else if(type == Solution2Cycles::SWAP_BETWEEN_CYCLES){

        this->swapVerticesBetweenCycles(a, b);
    }
}