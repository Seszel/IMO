#include "util_functions.hpp"

const std::string getPathToWorkspaceFolder(){

    char pathName[FILENAME_MAX];
    getcwd(pathName, FILENAME_MAX);

    std::string directory(pathName);
    directory += "/";

    auto pos = directory.rfind("/lab/");
    if(pos == std::string::npos){
        std::cerr << "cannot find directory" << std::endl;
        return "";
    }

    directory = directory.substr(0, pos + 1);
    directory += "lab/";
    return directory;

}

const std::size_t getHashOfMove(Move move){

    return std::hash<std::string>{}(std::to_string(move.a) + "_" + std::to_string(move.b) + "_" + std::to_string(move.type) + std::to_string(move.cyc_num));
}

const int isApplicable(Solution2Cycles & solution, Move move){
    return APPLICABLE;
    // check if the move is applicable
    bool b1 = (solution[move.cyc_num][move.a] == move.a_v);
    bool b2 = (solution[move.cyc_num][move.b] == move.b_v);

    if(b1 && b2){
        return NOT_APPLICABLE;
    }

    // check if move can be applied in the future
    b1 = (solution[move.cyc_num][move.a] == move.b_v);
    b2 = (solution[move.cyc_num][move.b] == move.a_v);

    if(!(b1 && b2)){
        //in the future
        return 2;
    }

    return APPLICABLE;
}

int getNumberOfCommonVertices(std::vector<int> a, std::vector<int> b){

    int cnt = 0;
    for(int i = 0; i < a.size(); i ++){
        auto it = std::find(b.begin(), b.end(), a[i]);
        if(it != b.end())
            cnt ++;
    }
    return cnt;
}

void dfs(int v, int p, std::vector<bool> & visited, int timer, std::vector<int> & low, 
        std::vector<int> & tin, std::vector<std::vector<int> > & adj,
        std::vector<std::pair<int, int> > & bridges) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = std::min(low[v], tin[to]);
        } else {
            dfs(to, v, visited, timer, low, tin, adj, bridges);
            low[v] = std::min(low[v], low[to]);
            if (low[to] > tin[v])
                bridges.push_back({v, to});
        }
    }
}

void dfs_cutpoints(int v, int p, std::vector<bool> & visited, int timer, std::vector<int> & low, 
        std::vector<int> & tin, std::vector<std::vector<int> > & adj,
        std::vector<int> & ap) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = std::min(low[v], tin[to]);
        } else {
            dfs_cutpoints(to, v, visited, timer, low, tin, adj, ap);
            low[v] = std::min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                ap.push_back(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        ap.push_back(v);
}