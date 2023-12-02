#include <functional>
#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>
#include <queue>

class ExpressionParser {
public:
    [[nodiscard]] std::function<double(double)> parse(const std::string& expression) const;

    std::function<double(double)> parseExpression(std::istringstream& iss) const;
    std::function<double(double)> parseTerm(std::istringstream& iss) const;
    std::function<double(double)> parseFactor(std::istringstream& iss) const;
    std::function<double(double)> parseNumber(std::istringstream& iss) const;

    std::function<double(double)> parseNumberOrVariable(std::istringstream &iss) const;
};
