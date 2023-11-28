#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
class ExpressionParser {
public:
    std::function<double(double)> parse(const std::string& expression) const;
    double parseNumber(std::istringstream& iss) const;
    std::function<double(double)> parseExpression(std::istringstream& iss) const;
    std::function<double(double)> parseTerm(std::istringstream& iss) const;
    std::function<double(double)> parseFactor(std::istringstream& iss) const;
};
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