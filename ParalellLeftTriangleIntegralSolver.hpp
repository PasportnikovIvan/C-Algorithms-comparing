#include <functional>
#include <thread>
#include <mutex>

class ParalellLeftTriangleIntegralSolver{
public:
    static double leftRectangleIntegration(const std::function<double(double)>& f, double a, double b, int n);
};