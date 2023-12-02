#include "integral.hpp"
#include <iostream>
#include <sstream>

// Function for calculating the definite integral by the method of left rectangles
double Integral::leftRectangleIntegration(const std::function<double(double)>& f, double a, double b, int n) {
    double h = (b - a) / n;
    double integral = 0.0;
    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        integral += f(x);
    }
    return integral * h;
}

// Function for calculating the definite integral by the trapezoidal method
double Integral::trapezoidalIntegration(const std::function<double(double)>& f, double a, double b, int n) {
    double h = (b - a) / n;
    double integral = 0.0;
    for (int i = 0; i < n; ++i) {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;

        double A = (f(x1) - 2 * f((x0 + x1) / 2) + f(x0)) / (2 * h * h);
        double B = (f(x1) - f(x0)) / h - A * (x1 + x0) / 2;
//        double C = f(x0) - A * x0 * x0 - B * x0;
        integral += (f(x0) + f(x1)) / 2;
    }
    return integral * h;
}

// Read function parameters from input
void Integral::read(std::istream& in) {
    std::string line;
    std::cout << "Enter function parameters (f, a, b, n): ";

    if (std::getline(in, line)) {
        std::stringstream ss(line);
        char comma;

        // Read the function and check for successful parsing
        if (std::getline(ss, functionStr, ',')) {
            // Read the values and check for successful parsing
            if (ss >> a >> comma >> b >> comma >> n && comma == ',') {
                valid = true;
            } else {
                std::cerr << "Error: Invalid input format. Please enter values separated by commas." << std::endl;
                valid = false;
            }
        } else {
            std::cerr << "Error: Invalid function input." << std::endl;
            valid = false;
        }
    } else {
        std::cerr << "Error: Failed to read input." << std::endl;
        valid = false;
    }
}

// Check if the input parameters are valid
bool Integral::isValid() const {
    return valid;
}

// Get lower limit of integration
double Integral::getA() const {
    return a;
}

// Get upper limit of integration
double Integral::getB() const {
    return b;
}

// Get number of subintervals
int Integral::getN() const {
    return n;
}

// Get the parsed function
std::function<double(double)> Integral::getFunction() const {
    return parser.parse(functionStr);
}