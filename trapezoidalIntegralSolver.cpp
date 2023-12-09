#include "trapezoidalIntegralSolver.hpp"
// Function for calculating the definite integral by the trapezoidal method
double trapezoidalIntegralSolver::trapezoidalIntegration(const std::function<double(double)>& f, double a, double b, int n) {
    double h = (b - a) / n;
    double integral = 0.0;
    for (int i = 0; i < n; ++i) {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;

        //double A = (f(x1) - 2 * f((x0 + x1) / 2) + f(x0)) / (2 * h * h);
        //double B = (f(x1) - f(x0)) / h - A * (x1 + x0) / 2;
        //double C = f(x0) - A * x0 * x0 - B * x0;
        integral += (f(x0) + f(x1)) / 2;
    }
    return integral * h;
}