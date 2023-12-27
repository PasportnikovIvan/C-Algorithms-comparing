#include <stack>
#include "DFS.hpp"

DFS::DFS(const Graph& graph) : graph(graph), visited(graph.getNumVertices(), false) {}

std::vector<int> DFS::dfs(int src) {
    std::stack<int> s;
    std::vector<int> path;

    s.push(src);
    visited[src] = true;

    while (!s.empty()) {
        int v = s.top();
        s.pop();
        path.push_back(v);

        for (const auto& neighbor : graph.getNeighbors(v)) {
            int neighbor_vertex = neighbor.first;
            if (!visited[neighbor_vertex]) {
                s.push(neighbor_vertex);
                visited[neighbor_vertex] = true;
            }
        }
    }

    return path;
}
