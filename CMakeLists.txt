cmake_minimum_required(VERSION 3.26)
project(sem_work)

set(CMAKE_CXX_STANDARD 17)

add_executable(        sem_work main.cpp
        DFS.cpp
        DFS.hpp
        Dijkstra.cpp
        Dijkstra.hpp
        Graph.cpp
        Graph.hpp
        ThreadSafeQueue.hpp
)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(sem_work Threads::Threads)