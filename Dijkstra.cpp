#include "Dijkstra.hpp"
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

Dijkstra::Dijkstra(const Graph& graph) : graph(graph), dist(graph.getNumVertices(), std::numeric_limits<int>::max()), prev(graph.getNumVertices(), -1) {}

std::vector<int> Dijkstra::shortestPath(int src, int dest) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& neighbor : graph.getNeighbors(u)) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<int> path;
    for (int v = dest; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    return path;
}
