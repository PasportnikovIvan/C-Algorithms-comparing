#include <iostream>
#include <chrono>
#include "integral.hpp"

int main() {
    Integral calc;
    calc.read(std::cin);

    if (calc.isValid()) {
        std::cout << "Function parameters are valid" << std::endl;

        double a = calc.getA();
        double b = calc.getB();
        int n = calc.getN();
        std::function<double(double)> function = calc.getFunction();

        auto start_left_triangles = std::chrono::high_resolution_clock::now();
        double result_left_triangles = Integral::leftRectangleIntegration(function, a, b, n);
        auto end_left_triangles = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_left_triangles = end_left_triangles - start_left_triangles;
        std::cout << "Left rectangle integration result: " << result_left_triangles << std::endl;
        std::cout << "Time taken by left rectangle integration: " << duration_left_triangles.count() << " seconds" << std::endl;

        auto start_trapezoidal = std::chrono::high_resolution_clock::now();
        double result_trapezoidal = Integral::trapezoidalIntegration(function, a, b, n);
        auto end_trapezoidal = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_trapezoidal = end_trapezoidal - start_trapezoidal;
        std::cout << "Trapezoidal integration result: " << result_trapezoidal << std::endl;
        std::cout << "Time taken by trapezoidal integration: " << duration_trapezoidal.count() << " seconds" << std::endl;

    } else {
        std::cout << "Invalid function parameters" << std::endl;
        return 1;
    }

    return 0;
}
