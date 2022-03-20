#include "instanceTSP.hpp"

std::string ltrim(const std::string &s) {
	return std::regex_replace(s, std::regex("^:\\s+"), std::string(""));
}

std::string rtrim(const std::string &s) {
	return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string &s) {
	return ltrim(rtrim(s));
}

void InstanceTSP::readFromFile(std::string path){

    std::fstream file;

    file.open(path, std::ios::in);

    if (file.good()){

        std::string line;
        std::string delimiter = ":";

        bool READING_NODES = false;

        getline(file, line);

        while (line != "EOF"){

            std::vector<std::string> items;
            size_t pos = 0;

            if(READING_NODES == false){

                pos = line.find(delimiter);
                items.push_back(line.substr(0, pos));
                line.erase(0, pos);
                items.push_back(line.substr(0, line.length()));

                if (items[0] == "NAME"){
                    this->name = trim(items[1]);
                }
                else if (items[0] == "TYPE"){
                    this->type = trim(items[1]);
                }
                else if (items[0] == "COMMENT"){
                    this->comment = trim(items[1]);
                }
                else if (items[0] == "DIMENSION"){
                    this->dimension = stoi(trim(items[1]));
                }
                else if (items[0].find("EDGE_WEIGHT_TYPE") != std::string::npos){
                    this->edgeWeightType = trim(items[1]);
                }
                else if (items[0] == "NODE_COORD_SECTION"){
                    
                    READING_NODES = true;
                }
            }
            else {
                
                pos = line.find(' ');
                while(pos != std::string::npos){
                    items.push_back(line.substr(0, pos));
                    line.erase(0,pos + 1);
                    pos = line.find(' ');
                }
                items.push_back(line);
                
                Point<int> point;
                point.x = stoi(items[1]);
                point.y = stoi(items[2]);

                this->nodes.push_back(point);
            }

            getline(file, line);
        }
        file.close();
    }
    int x2, y2, d;
    for (int i=0; i<nodes.size(); i++){
        std::vector<int > temp;
        for (int j=0; j<nodes.size(); j++){
            x2 = pow((nodes[i].x - nodes[j].x), 2);
            y2 = pow((nodes[i].y - nodes[j].y), 2);
            d = (int)(sqrt(x2 + y2) + 0.5);
            if (d==0) {
                d = std::numeric_limits<int>::max();
            }
            temp.push_back(d);
        }
        this->matrix.push_back(temp);
    } 
}

void InstanceTSP::writeData(){}

const std::string InstanceTSP::getName() const{

    return this->name;
}