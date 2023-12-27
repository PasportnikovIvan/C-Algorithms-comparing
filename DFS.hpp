#ifndef DFS_H
#define DFS_H

#include "Graph.hpp"
#include <vector>

class DFS {
public:
    DFS(const Graph& graph);
    std::vector<int> dfs(int src);

private:
    Graph graph;
    std::vector<bool> visited;
};

#endif
