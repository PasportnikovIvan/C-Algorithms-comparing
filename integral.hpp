#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include "parser.hpp"

class Integral {

public:
    std::vector<std::vector<long double>> function;
    //calling the leftRectangleIntegration method
    static double leftRectangleIntegration(const std::function<double(double)>& f,
                                           double a, double b, int n);
    // Function for calculating the definite integral by the trapezoidal method
    static double trapezoidalIntegration(const std::function<double(double)>& f,
                                         double a, double b, int n);

// Reads the function from the input stream
    void read(std::istream& in);
    std::function<double(double)> getFunction() const;
    bool isValid() const;
    double getA() const;
    double getB() const;
    int getN() const;
private:
    double a;
    double b;
    int n;
    std::string functionStr;
    bool valid;
    ExpressionParser parser;
};