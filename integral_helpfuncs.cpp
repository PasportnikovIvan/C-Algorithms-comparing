#include "integral_helpfuncs.hpp"
#include <iostream>
#include <sstream>

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