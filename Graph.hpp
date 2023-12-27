#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>

class Graph {
public:
    Graph(int num_vertices);
    void addEdge(int src, int dest, int weight);
    std::vector<std::pair<int, int>> getNeighbors(int vertex);
    int getNumVertices() const;

private:
    int num_vertices;
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacency_list;
};

#endif
