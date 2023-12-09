#include <iostream>
#include <chrono>
#include "integral_helpfuncs.hpp"
#include "leftRectangleIntegralSolver.hpp"
#include "ParalellLeftTriangleIntegralSolver.hpp"
#include "trapezoidalIntegralSolver.hpp"
#include "ParallelITrapezoidalIntegralSolver.hpp"

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}
void printHelp(){
    std::cout << "Usage: ./integral {-h | --help } {-s|-a|-p} {-S|-F}" << std::endl;
    std::cout << "Format for inserting the function: function in c++ format(only x variable is supported), down border, up border, precision(count of subintervals)" << std::endl;
    std::cout << "Example1: -lr 2*x,0,2,100" << std::endl;
    std::cout << "Example2: -tr x^2,-3,2,1000" << std::endl;
    std::cout << "Example3: -plr sin(x),1,5,5" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help Show this help message and exit" << std::endl;
    std::cout << "  -lr <function> <a> <b> <n> Use left rectangle classic algorithm only" << std::endl;
    std::cout << "  -tr <function> <a> <b> <n> Use triangle classic algorithm only" << std::endl;
    std::cout << "  -plr <function> <a> <b> <n> Use thread left rectangle algorithm solver" << std::endl;
    std::cout << "  -ptr <function> <a> <b> <n> Use thread triangle algorithm solver" << std::endl;
    std::cout << "  -e, --exit Exit and close the program" << std::endl;
}

int main() {
    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "--exit" || input == "-e") {
            break;
        }
        else if (input == "-h" || input == "--help") {
            printHelp();
            return 0;
        }
        else if (input == "-lr") {
            Integral calc;
            calc.read(std::cin);
            if (calc.isValid()) {
                auto start_left_triangle = std::chrono::high_resolution_clock::now();
                calc.printSolution(leftRectangleIntegralSolver::leftRectangleIntegration);
                auto end_left_triangle = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end_left_triangle - start_left_triangle).count() << " ms to finish.\n";
            }
        } else if (input == "-plr") {
            Integral calc;
            calc.read(std::cin);
            if (calc.isValid()) {
                auto start_left_triangle = std::chrono::high_resolution_clock::now();
                calc.printSolution(ParalellLeftTriangleIntegralSolver::leftRectangleIntegration);
                auto end_left_triangle = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end_left_triangle - start_left_triangle).count() << " ms to finish.\n";
            }
        } else if (input == "-tr") {
            Integral calc;
            calc.read(std::cin);
            if (calc.isValid()) {
                auto start_left_triangle = std::chrono::high_resolution_clock::now();
                calc.printSolution(trapezoidalIntegralSolver::trapezoidalIntegration);
                auto end_left_triangle = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end_left_triangle - start_left_triangle).count() << " ms to finish.\n";
            }
        } else if (input == "-ptr") {
            Integral calc;
            calc.read(std::cin);
            if (calc.isValid()) {
                auto start_left_triangle = std::chrono::high_resolution_clock::now();
                calc.printSolution(ParalellTrapezoidalIntegralSolver::trapezoidalIntegration);
                auto end_left_triangle = std::chrono::high_resolution_clock::now();
                std::cout << "Needed " << to_ms(end_left_triangle - start_left_triangle).count() << " ms to finish.\n";
            }
        }
        else {
            std::cout << "Invalid method. Use -h,--help to see supported methods" << std::endl;
        }
    }
    return 0;
}