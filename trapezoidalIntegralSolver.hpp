#include <functional>
#include <vector>
#include <iostream>
#include <sstream>

class trapezoidalIntegralSolver{
public:
    // Function for calculating the definite integral by the trapezoidal method
    static double trapezoidalIntegration(const std::function<double(double)>& f,
                                         double a, double b, int n);
};