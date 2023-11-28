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