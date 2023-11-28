#include <iostream>
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

        ExpressionParser parser;
        std::function<double(double)> expression = parser.parse("x*x + 2*x + 1");

        double result_left_triangles = calc.leftRectangleIntegration(function, a, b, n);
        std::cout << "Left rectangle integration result: " << result_left_triangles << std::endl;

        double result_trapezoidal = calc.trapezoidalIntegration(function, a, b, n);
        std::cout << "Left rectangle integration result: " << result_trapezoidal << std::endl;

    } else {
        std::cout << "Invalid function parameters" << std::endl;
        return 1;
    }
}