#include <iostream>
#include <chrono>
#include "integral_helpfuncs.hpp"
#include "leftRectangleIntegralSolver.hpp"
#include "trapezoidalIntegralSolver.hpp"

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}
void printHelp(){
    std::cout << "Usage: ./integral {-h | --help } {-s|-a|-p} {-S|-F}" << std::endl;
    std::cout << "Format for inserting: function in c++ format, down border, up border, precision(count of subintervals)" << std::endl;
    std::cout << "Example1: 2*x,0,2,100" << std::endl;
    std::cout << "Example2: x^2,-3,2,1000" << std::endl;
    std::cout << "Example3: sin(x),1,5,5" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help Show this help message and exit" << std::endl;
    std::cout << "  -a Use async solver" << std::endl;
    std::cout << "  -p Use parallel solver" << std::endl;
    std::cout << "  -s Use classic solver" << std::endl;
    std::cout << "  -lr Use left rectangle algorithm only" << std::endl;
    std::cout << "  -tr Use triangle algorithm only" << std::endl;
}
int main() {
    Integral calc;
    calc.read(std::cin);

    if (calc.isValid()) {
        std::cout << "Function parameters are valid" << std::endl;

        double a = calc.getA();
        double b = calc.getB();
        int n = calc.getN();
        std::function<double(double)> function = calc.getFunction();

        // Set precision for output
//        std::cout << std::fixed << std::setprecision(12);  // Adjust precision as needed
        auto start_left_triangle = std::chrono::high_resolution_clock::now();
        double result_left_triangles = leftRectangleIntegralSolver::leftRectangleIntegration(function, a, b, n);
        auto end_left_triangle = std::chrono::high_resolution_clock::now();
        std::cout << "Left rectangle integration result: " << result_left_triangles << std::endl;
        std::cout << "Needed " << to_ms(end_left_triangle - start_left_triangle).count() << " ms to finish.\n";

        auto start_trapezoidal = std::chrono::high_resolution_clock::now();
        double result_trapezoidal = trapezoidalIntegralSolver::trapezoidalIntegration(function, a, b, n);
        auto end_trapezoidal = std::chrono::high_resolution_clock::now();
        std::cout << "Trapezoidal integration result: " << result_trapezoidal << std::endl;
        std::cout << "Needed " << to_ms(end_trapezoidal - start_trapezoidal).count() << " ms to finish.\n";

    } else {
        std::cout << "Invalid function parameters" << std::endl;
        return 1;
    }

    return 0;
}
