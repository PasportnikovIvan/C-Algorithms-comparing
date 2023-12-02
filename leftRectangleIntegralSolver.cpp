#include "leftRectangleIntegralSolver.hpp"

// Function for calculating the definite integral by the method of left rectangles
double leftRectangleIntegralSolver::leftRectangleIntegration(const std::function<double(double)>& f, double a, double b, int n) {
    double h = (b - a) / n;
    double integral = 0.0;
    for (int i = 0; i < n; ++i) {
        double x = a + i * h;
        integral += f(x);
    }
    return integral * h;
}
