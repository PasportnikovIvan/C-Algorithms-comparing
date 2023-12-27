#include "Graph.hpp"
#include "DFS.hpp"
#include "Dijkstra.hpp"
#include "ThreadSafeQueue.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

/*
 * If you're running the program from an IDE, you'll need to enter the command-line arguments in the IDE's settings. Here's how you can do this in some popular IDEs:

Visual Studio: Right-click on your project in the Solution Explorer, then choose Properties. Open the "Configuration Properties" tree element, and choose "Debugging". In the right pane, there is a line called "Command Arguments". You can enter your command-line arguments there for testing, and they will be automatically passed to your program when you run it.
Code::Blocks: Choose "Project -> Set program’s arguments".
CLion: Go to Run -> Edit Configurations, select your configuration, and enter your command-line arguments in the "Program arguments" field.
 */
void printHelp() {
    std::cout << "Usage: ./sem_work [--help] [--dfs <src>] [--dijkstra <src> <dest>] [--PDFS <src>] [--PDKS <src> <dest>] [--exit]\n";
    std::cout << "Example1: ./sem_work --dfs 0\n";
    std::cout << "Example2: ./sem_work --PDFS 0\n";
    std::cout << "Example3: ./sem_work --dijkstra 0 4\n";
    std::cout << "Example4: ./sem_work --PDKS 0 4\n";
    std::cout << "Example5: ./sem_work --help\n";
    std::cout << "Options:\n";
    std::cout << " --help          Print this help message.\n";
    std::cout << " --dfs <src>       Perform a depth-first search from vertex src.\n";
    std::cout << " --dijkstra <src> <dest> Perform Dijkstra's algorithm from vertex src to vertex dest.\n";
    std::cout << " --PDFS <src> Perform a parallel depth-first search from vertex src.\n";
    std::cout << " --PDKS <src> <dest> Perform parallel Dijkstra's algorithm from vertex src to vertex dest.\n";
    std::cout << " --exit Exit and close the program\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Error: Missing command-line arguments.\n";
        printHelp();
        return 1;
    }

    std::string option = argv[1];

    if (option == "--help") {
        printHelp();
        return 0;
    }

    if (option == "--exit") {
        return 0;
    }

//    Graph graph(5);
//    graph.addEdge(0, 1, 1);
//    graph.addEdge(0, 4, 1);
//    graph.addEdge(1, 2, 1);
//    graph.addEdge(1, 4, 1);
//    graph.addEdge(2, 3, 1);
//    graph.addEdge(3, 4, 1);

    Graph graph(100000);
    for (int i = 0; i < 100000; ++i) {
        graph.addEdge(i, (i + 1) % 100000, 1); // connectin' each vertex to the next one
    }

    if (option == "--dfs") {
        if (argc != 3) {
            std::cout << "Error: Missing source vertex for depth-first search.\n";
            printHelp();
            return 1;
        }

        int src = std::stoi(argv[2]);
        DFS dfs(graph);
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> path = dfs.dfs(src);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Depth-first search from vertex " << src << ":\n";
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";
        std::cout << "Time taken by depth-first search: " << to_ms(end - start).count() << " ms\n";
    } else if (option == "--dijkstra") {
        if (argc != 4) {
            std::cout << "Error: Missing source or destination vertex for Dijkstra's algorithm.\n";
            printHelp();
            return 1;
        }

        int src = std::stoi(argv[2]);
        int dest = std::stoi(argv[3]);
        Dijkstra dijkstra(graph);
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> path = dijkstra.shortestPath(src, dest);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Shortest path from vertex " << src << " to vertex " << dest << ":\n";
        for (int vertex : path) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";
        std::cout << "Time taken by Dijkstra's algorithm: " << to_ms(end - start).count() << " ms\n";
    } else if (option == "--PDKS") {
        if (argc != 4) {
            std::cout << "Error: Missing source or destination vertex for parallel Dijkstra's algorithm.\n";
            printHelp();
            return 1;
        }

        int src = std::stoi(argv[2]);
        int dest = std::stoi(argv[3]);
        Dijkstra dijkstra(graph);
        auto start = std::chrono::high_resolution_clock::now();

        ThreadSafeQueue<std::vector<int>> paths;

        std::vector<std::thread> threads;
        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.push_back(std::thread([&]() {
                std::vector<int> temp_path = dijkstra.shortestPath(src, dest);
                paths.push(temp_path);
            }));
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::vector<int> final_path = paths.pop();
        while (!paths.empty()) {
            std::vector<int> temp_path = paths.pop();
            if (final_path.size() > temp_path.size()) {
                final_path = temp_path;
            }
        }

        std::cout << "Parallel Dijkstra Shortest path from vertex " << src << " to vertex " << dest << ":\n";
        for (int vertex : final_path) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";

        std::cout << "Time taken by parallel Dijkstra's algorithm: " << to_ms(end - start).count() << " ms\n";
    } else if (option == "--PDFS") {
        if (argc != 3) {
            std::cout << "Error: Missing source vertex for parallel depth-first search.\n";
            printHelp();
            return 1;
        }

        int src = std::stoi(argv[2]);
        DFS dfs(graph);
        auto start = std::chrono::high_resolution_clock::now();

        ThreadSafeQueue<std::vector<int>> paths;

        std::vector<std::thread> threads;
        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.push_back(std::thread([&]() {
                std::vector<int> temp_path = dfs.dfs(src);
                paths.push(temp_path);
            }));
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Parallel depth-first search from vertex " << src << ":\n";
        while (!paths.empty()) {
            std::vector<int> temp_path = paths.pop();
            for (int i = 0; i < temp_path.size() - 1; ++i) {
                std::cout << temp_path[i] << "-" << temp_path[i+1] << " ";
            }
            std::cout << "\n";
        }

        std::cout << "Time taken by parallel depth-first search: " << to_ms(end - start).count() << " ms\n";
    } else {
        std::cout << "Error: Invalid command-line argument.\n";
        printHelp();
        return 1;
    }

    return 0;
}