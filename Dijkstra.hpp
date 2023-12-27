#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.hpp"
#include <vector>

class Dijkstra {
public:
    Dijkstra(const Graph& graph);
    std::vector<int> shortestPath(int src, int dest);

private:
    Graph graph;
    std::vector<int> dist;
    std::vector<int> prev;
};

#endif
