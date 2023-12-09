#include <functional>
#include <thread>
#include <mutex>

class ParalellTrapezoidalIntegralSolver{
public:
    // Function for calculating the definite integral by the trapezoidal method with threads
    static double trapezoidalIntegration(const std::function<double(double)> &f, double a, double b, int n);
};