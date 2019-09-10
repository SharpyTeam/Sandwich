//
// Created by Ilya on 10.09.2019.
//

#ifndef SANDWICH_OPERATOR_HPP
#define SANDWICH_OPERATOR_HPP

namespace sw {

class Operator {
    char op;
protected:
    Operator() : op(' ') {}

    explicit Operator(char c) : op(c) {}

public:
    virtual char GetSymbol() const {
        return op;
    }

    virtual double Apply(double f_operand, double s_operand) const = 0;

    virtual ~Operator() = default;
};

class PlusOperator : public Operator {
public:
    PlusOperator() : Operator('+') {}

    double Apply(double f_operand, double s_operand) const override {
        return f_operand + s_operand;
    }
};

class MinusOperator : public Operator {
public:
    MinusOperator() : Operator('-') {}

    double Apply(double f_operand, double s_operand) const override {
        return f_operand - s_operand;
    }
};

class MultiplicationOperator : public Operator {
public:
    MultiplicationOperator() : Operator('*') {}

    double Apply(double f_operand, double s_operand) const override {
        return f_operand * s_operand;
    }
};

class DivisionOperator : public Operator {
public:
    DivisionOperator() : Operator('/') {}

    double Apply(double f_operand, double s_operand) const override {
        return f_operand / s_operand;
    }
};

}


#endif //SANDWICH_OPERATOR_HPP
