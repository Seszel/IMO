#include "instanceTSP.hpp"

void InstanceTSP::readFromFile(std::string path){

    std::fstream file;

    file.open(path, std::ios::in);

    if (file.good()){

        std::string line;
        std::string space_delimiter = " ";

        while (!file.eof()){

            getline(file, line);

            std::vector<std::string> items;
            size_t pos = 0;

            while ((pos = line.find(space_delimiter)) != std::string::npos) {
                items.push_back(line.substr(0, pos));
                line.erase(0, pos + space_delimiter.length());
            }

            if (items[0] == "NAME:"){
                InstanceTSP::name = items[1];
            }
            else if (items[0] == "TYPE:"){
                InstanceTSP::type = items[1];
            }
            else if (items[0] == "COMMENT:"){
                InstanceTSP::comment = items[1];
            }
            else if (items[0] == "DIMENSION:"){
                InstanceTSP::dimension = stoi(items[1]);
            }
            else if (items[0] == "EDGE_WEIGHT_TYPE"){
                InstanceTSP::edgeWeightType = items[2];
            }
            else if (items[0] == "NODE_COORD_SECTION" || items[0] == "EOF"){
                ;
                std::cout << "yay" << std::endl;
            }
            else {
                Point<int> point;
                point.x = stoi(items[1]);
                point.y = stoi(items[2]);

                InstanceTSP::nodes.push_back(point);
            }
        
        }
        file.close();

        std::cout << InstanceTSP::name << std::endl;
        std::cout << InstanceTSP::type << std::endl;
        std::cout << InstanceTSP::comment << std::endl;
        std::cout << InstanceTSP::dimension << std::endl;
        std::cout << InstanceTSP::edgeWeightType << std::endl;
        for (auto const& n : InstanceTSP::nodes){
            std::cout << (n.x, n.y) << std::endl;
        }
    }   
}

void InstanceTSP::writeData(){}