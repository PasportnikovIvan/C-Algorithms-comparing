#include "integral.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

std::function<double(double)> ExpressionParser::parse(const std::string& expression) const {
    std::istringstream iss(expression);
    return parseExpression(iss);
}

std::function<double(double)> ExpressionParser::parseExpression(std::istringstream& iss) const {
    std::function<double(double)> value = parseTerm(iss);
    char op;

    while (iss >> op) {
        if (op == '+' || op == '-') {
            std::function<double(double)> term = parseTerm(iss);
            value = [value, term, op](double x) {
                return (op == '+') ? value(x) + term(x) : value(x) - term(x);
            };
        } else {
            iss.putback(op);
            break;
        }
    }

    return value;
}

std::function<double(double)> ExpressionParser::parseTerm(std::istringstream& iss) const {
    std::function<double(double)> value = parseFactor(iss);
    char op;

    while (iss >> op) {
        if (op == '*' || op == '/') {
            std::function<double(double)> factor = parseFactor(iss);
            value = [value, factor, op](double x) {
                return (op == '*') ? value(x) * factor(x) : value(x) / factor(x);
            };
        } else {
            iss.putback(op);
            break;
        }
    }

    return value;
}
std::function<double(double)> ExpressionParser::parseFactor(std::istringstream& iss) const {
    char next;
    iss >> next;

    if (next == '(') {
        std::function<double(double)> value = parseExpression(iss);
        iss >> next; // Read the closing parenthesis
        return value;
    } else if (std::isalpha(next)) { // Check if it's a variable like 'x'
        std::string variable;
        variable += next;
        while (iss.get(next) && (std::isalnum(next) || next == '_')) {
            variable += next;
        }
        iss.putback(next);

        if (variable == "x") {
            return [this](double x) { return x; };
        } else {
            std::cerr << "Error: Unsupported variable '" << variable << "'" << std::endl;
            iss.setstate(std::ios::failbit);
            return [](double) { return 0.0; }; // Handle unsupported variables gracefully
        }
    } else {
        iss.putback(next);
        double numericValue = parseNumber(iss);
        return [numericValue](double x) { return numericValue; };
    }
}

double ExpressionParser::parseNumber(std::istringstream& iss) const {
    double value;
    iss >> value;
    return value;
}

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
        double C = f(x0) - A * x0 * x0 - B * x0;

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