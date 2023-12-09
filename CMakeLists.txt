cmake_minimum_required(VERSION 3.26)
project(sem_work)

set(CMAKE_CXX_STANDARD 17)

add_executable(        sem_work main.cpp
        integral_helpfuncs.hpp
        integral_helpfuncs.cpp
        parser.hpp
        parser.cpp
        leftRectangleIntegralSolver.hpp
        leftRectangleIntegralSolver.cpp
        trapezoidalIntegralSolver.cpp
        trapezoidalIntegralSolver.hpp
        ParallelTrapezoidalIntegralSolver.cpp
        ParallelLeftTriangleIntegralSolver.cpp
        ParallelLeftTriangleIntegralSolver.hpp
        ParallelTrapezoidalIntegralSolver.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)