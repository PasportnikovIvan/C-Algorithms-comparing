cmake_minimum_required(VERSION 3.26)
project(sem_work)

set(CMAKE_CXX_STANDARD 17)

add_executable(sem_work main.cpp
        integral.hpp
        integral.cpp
        parser.hpp
        parser.cpp)
