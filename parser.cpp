#include "parser.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

std::function<double(double)> ExpressionParser::parse(const std::string& expression) const {
    std::istringstream iss(expression);
    return parseExpression(iss);
}

std::function<double(double)> ExpressionParser::parseExpression(std::istringstream& iss) const {
    std::function<double(double)> value = parseTerm(iss);
    char op;

    while (iss >> op) {
        if (op == '+' || op == '-') {
            std::function<double(double)> term = parseTerm(iss);
            value = [value, term, op](double x) {
                return (op == '+') ? value(x) + term(x) : value(x) - term(x);
            };
        } else {
            iss.putback(op);
            break;
        }
    }

    return value;
}

std::function<double(double)> ExpressionParser::parseTerm(std::istringstream& iss) const {
    std::function<double(double)> value = parseFactor(iss);
    char op;

    while (iss >> op) {
        if (op == '*' || op == '/') {
            std::function<double(double)> factor = parseFactor(iss);
            value = [value, factor, op](double x) {
                return (op == '*') ? value(x) * factor(x) : value(x) / factor(x);
            };
        } else {
            iss.putback(op);
            break;
        }
    }

    return value;
}
std::function<double(double)> ExpressionParser::parseFactor(std::istringstream& iss) const {
    char next;
    iss >> next;

    if (next == '(') {
        std::function<double(double)> value = parseExpression(iss);
        iss >> next; // Read the closing parenthesis
        return value;
    } else if (std::isalpha(next)) { // Check if it's a variable like 'x' or 'pi'
        std::string variable;
        variable += next;
        while (iss.get(next) && (std::isalnum(next) || next == '_')) {
            variable += next;
        }
        iss.putback(next);

        if (variable == "x") {
            return [this](double x) { return x; };
        } else if (variable == "pi") {
            return [](double) { return M_PI; }; // M_PI is a constant defined in cmath
        } else {
            std::cerr << "Error: Unsupported variable '" << variable << "'" << std::endl;
            iss.setstate(std::ios::failbit);
            return [](double) { return 0.0; }; // Handle unsupported variables gracefully
        }
    } else {
        iss.putback(next);
        double numericValue = parseNumber(iss);
        return [numericValue](double x) { return numericValue; };
    }
}

double ExpressionParser::parseNumber(std::istringstream& iss) const {
    std::string str;
    iss >> str;

    if (str == "pi") {
        return M_PI; // M_PI is a constant defined in cmath
    }

    std::istringstream strStream(str);
    double value;
    strStream >> value;
    return value;
}
