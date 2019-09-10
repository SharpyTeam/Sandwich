//
// Created by Ilya on 10.09.2019.
//

#ifndef SANDWICH_STD_CALCULATOR_HPP
#define SANDWICH_STD_CALCULATOR_HPP

#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "operator.hpp"

namespace sw {

class StdCalculator {
    std::stack<double> operands_stack;
    std::unordered_map<char, Operator *> operators;

    double result;

    virtual void EvalExpression(const std::vector<std::string> &expr) {
        for (const std::string &token : expr) {
            if (token.length() == 1 && !std::isdigit(token[0])) {
                if (operands_stack.size() < 2) {
                    throw std::runtime_error("Not enough operands passed to evaluate the expression");
                }
                double f_operand = operands_stack.top();
                operands_stack.pop();
                double s_operand = operands_stack.top();
                operands_stack.pop();
                double value = operators[token[0]]->Apply(f_operand, s_operand);
                operands_stack.push(value);
            }
            else {
                double num = std::atof(token.c_str());
                operands_stack.push(num);
            }
        }
        if (operands_stack.size() > 1)
        {
            throw std::runtime_error("Not enough operands passed to evaluate the expression");
        }
        result = operands_stack.top();
    }
public:
    StdCalculator(const std::vector<std::string> &expr) : result(0.0) {
        AddOperator(new PlusOperator);
        AddOperator(new MinusOperator);
        AddOperator(new MultiplicationOperator);
        AddOperator(new DivisionOperator);
        EvalExpression(expr);
    }

    double GetResult() const {
        return result;
    }

    virtual void AddOperator(Operator *op) {
        operators.emplace(op->GetSymbol(), op);
    }

    ~StdCalculator() {
        for (auto &o : operators) {
            delete o.second;
        }
    }
};

}

#endif //SANDWICH_STD_CALCULATOR_HPP
