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
}

void InstanceTSP::writeData(){}