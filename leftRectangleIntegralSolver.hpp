#include <vector>
#include <functional>
#include <iostream>
#include <sstream>

class leftRectangleIntegralSolver{
public:
    //Function for calculating the definite integral by the leftRectangleIntegration method
    static double leftRectangleIntegration(const std::function<double(double)>& f,
                                           double a, double b, int n);
};