#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include "parser.hpp"
#include "leftRectangleIntegralSolver.hpp"
#include "trapezoidalIntegralSolver.hpp"

#include "ParallelITrapezoidalIntegralSolver.hpp"
#include "ParalellLeftTriangleIntegralSolver.hpp"
class Integral {

public:
    std::vector<std::vector<long double>> function;
// Reads the function from the input stream
    void read(std::istream& in);
    [[nodiscard]] std::function<double(double)> getFunction() const;
    [[nodiscard]] bool isValid() const;
    [[nodiscard]] double getA() const;
    [[nodiscard]] double getB() const;
    [[nodiscard]] int getN() const;
    void printSolution(const std::function<double(const std::function<double(double)>&, double, double, int)>& algorithm) const;
private:
    double a;
    double b;
    int n;
    std::string functionStr;
    bool valid;
    ExpressionParser parser;
};