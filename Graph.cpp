#include "Graph.hpp"

Graph::Graph(int num_vertices) : num_vertices(num_vertices) {}

void Graph::addEdge(int src, int dest, int weight) {
    adjacency_list[src].push_back({dest, weight});
}

std::vector<std::pair<int, int>> Graph::getNeighbors(int vertex) {
    return adjacency_list[vertex];
}

int Graph::getNumVertices() const {
    return num_vertices;
}
