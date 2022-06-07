#include "myAlgorithm.hpp"

const Solution2Cycles MyAlgorithm::run(const InstanceTSP & instance){

    Solution2Cycles bestSolution = Solution2Cycles(*this->startSolution), currentSolution = Solution2Cycles(*this->startSolution);

    struct edge{
        int u;
        int v;
        int d;
    };
    std::vector<edge> edges;
    std::vector<std::vector<int> > adj;
    adj.resize(instance.dimension);
    std::vector<std::vector<int> > adj_matrix(instance.dimension);
    for(auto & v : adj_matrix)
        v.resize(instance.dimension, 0);
    int K = 199;
    for(int i = 0; i < instance.dimension; i++){
        auto kclosest = this->findKClosestVertices(i, K, instance);
        for(int u : kclosest){
            adj_matrix[i][u] = 1;
            adj_matrix[u][i] = 1;
        }
    }
    for(int i = 0; i < instance.dimension; i++){
        for(int j = i + 1; j < instance.dimension; j ++){
            if(adj_matrix[i][j] == 1){
                adj[i].push_back(j);  
                adj[j].push_back(i);
                edges.push_back({i,j,instance.matrix[i][j]});                
            }
        }
    }
    std::sort(edges.begin(), edges.end(), [](const edge & a, const edge & b){
        return a.d > b.d;
    });

    std::vector<int> degs(instance.dimension, 0);
    for(int i = 0; i < instance.dimension; i++){
        degs[i] = adj[i].size();
    }

    bool isgt2 = true;

    auto bridges = find_articulation_points(adj);
    if(bridges.size() > 0){
        std::cerr<< "found bridge at the beginning, stop" << std::endl;
    }
    std::cerr << edges.size() << std::endl;
    for(auto & e : edges){
        
        auto uv = std::find(adj[e.u].begin(), adj[e.u].end(), e.v);
        auto vu = std::find(adj[e.v].begin(), adj[e.v].end(), e.u);
        if(uv != adj[e.u].end() && vu != adj[e.v].end()){
            adj[e.u].erase(uv);
            adj[e.v].erase(vu);
        }
        else {
            std::cerr << " e " << std::endl;
        }
        auto ap = find_articulation_points(adj);
        if(ap.size() > 0){
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
            continue;
        }
        else{
            degs[e.u]--;
            degs[e.v]--;
        }
    }

    int cost = 0;
    int e = 0;
    for(int i = 0; i < adj.size(); i ++){
        for(int j = 0; j < adj[i].size(); j ++){
            cost += instance.matrix[i][adj[i][j]];
        }
        e += adj[i].size();
    }

    this->bestFoundSolution = new Solution2Cycles(bestSolution);

    return bestSolution;
}

void MyAlgorithm::setAvailableMoveTypes(std::vector<int> types){

    this->availableMoveTypes = types;
}

void MyAlgorithm::setStartingSolution(const Solution2Cycles * solution){

    this->startSolution = solution;
}

std::vector<std::pair<int, int> > MyAlgorithm::find_bridges(std::vector<std::vector<int> > & adj){
    int n = 200; // number of nodes

    std::vector<bool> visited;
    std::vector<int> tin, low;
    int timer;
    std::vector<std::pair<int, int> > bridges = {};

    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i,-1, visited, timer, low, tin, adj, bridges);
    }

    return bridges;
}

std::vector<int> MyAlgorithm::find_articulation_points(std::vector<std::vector<int> > & adj){
    int n = 200; // number of nodes

    std::vector<bool> visited;
    std::vector<int> tin, low;
    int timer;
    std::vector<int> ap;

    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs_cutpoints(i,-1, visited, timer, low, tin, adj, ap);
    }

    return ap;
}