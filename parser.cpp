#include "parser.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

std::function<double(double)> ExpressionParser::parse(const std::string& expression) const {
    std::istringstream iss(expression);
    return parseExpression(iss);
}

std::function<double(double)> ExpressionParser::parseExpression(std::istringstream& iss) const {
    std::function<double(double)> left = parseTerm(iss);

    char op;
    while (iss >> op && (op == '+' || op == '-')) {
        std::function<double(double)> right = parseTerm(iss);

        if (op == '+') {
            left = [left, right](double x) { return left(x) + right(x); };
        } else {
            left = [left, right](double x) { return left(x) - right(x); };
        }
    }

    iss.putback(op);
    return left;
}

std::function<double(double)> ExpressionParser::parseTerm(std::istringstream& iss) const {
    std::function<double(double)> left = parseFactor(iss);

    char op;
    while (iss >> op && (op == '*' || op == '/')) {
        std::function<double(double)> right = parseFactor(iss);

        if (op == '*') {
            left = [left, right](double x) { return left(x) * right(x); };
        } else {
            left = [left, right](double x) { return left(x) / right(x); };
        }
    }

    iss.putback(op);
    return left;
}

std::function<double(double)> ExpressionParser::parseFactor(std::istringstream& iss) const {
    char next;
    iss >> next;

    if (next == '(') {
        std::function<double(double)> value = parseExpression(iss);
        iss >> next; // Read the closing parenthesis
        return value;
    } else {
        iss.putback(next);
        return parseNumberOrVariable(iss);
    }
}
std::function<double(double)> ExpressionParser::parseNumberOrVariable(std::istringstream& iss) const {
    std::string token;
    char next;

    while (iss.get(next) && (std::isalnum(next) || next == '_' || next == '.')) {
        token += next;
    }
    iss.putback(next);

    if (!token.empty()) {
        if (token == "pi") {
            return [](double) { return M_PI; }; // M_PI is a constant defined in cmath
        } else if (std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]))) {
            std::istringstream strStream(token);
            double numericValue;
            strStream >> numericValue;
            return [numericValue](double) { return numericValue; };
        } else if (token == "x") {
            return [](double x) { return x; };
        } else {
            std::cerr << "Error: Unsupported variable '" << token << "'" << std::endl;
            iss.setstate(std::ios::failbit);
            return [](double) { return 0.0; }; // Handle unsupported variables gracefully
        }
    }

    return [](double) { return 0.0; };
}
