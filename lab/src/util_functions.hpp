#ifndef UTIL_FUNCTIONS_HPP
#define UTIL_FUNCTIONS_HPP

#include "algorithms/algorithm2cycles.hpp"

#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <unordered_map>

extern const std::string getPathToWorkspaceFolder();
extern const std::size_t getHashOfMove(Move);
extern int getNumberOfCommonVertices(std::vector<int> a, std::vector<int> b);

const int APPLICABLE = 0;
const int NOT_APPLICABLE = 1;

extern const int isApplicable(Solution2Cycles &, Move);
extern void dfs(int v, int p, std::vector<bool> & visited, int timer, std::vector<int> & low, 
        std::vector<int> & tin, std::vector<std::vector<int> > & adj,
        std::vector<std::pair<int, int> > & bridges);
extern void dfs_cutpoints(int v, int p, std::vector<bool> & visited, int timer, std::vector<int> & low, 
        std::vector<int> & tin, std::vector<std::vector<int> > & adj,
        std::vector<int> & ap);

#endif