#include "operator.hpp"
#include "number.hpp"
#include <math.h>

Operator::Operator(const ValueRef& left,
                   const ValueRef& right)
: m_Left(left)
, m_Right(right)
{
    if (!m_Left) {
        throw std::runtime_error("Operator must have left expression");
    }
    if (!m_Right) {
        throw std::runtime_error("Operator must have right expression");
    }
}

const ValueRef& Operator::left() const {
    return m_Left;
}

const ValueRef& Operator::right() const {
    return m_Right;
}


////////////////////////////////////////////////////////////////////////////////

OperatorAdd::OperatorAdd(const ValueRef& left,
                         const ValueRef& right)
: Operator(left ? left : std::make_shared<Number>(), right)
{ }

float OperatorAdd::evaluate() {
    return left()->evaluate() + right()->evaluate();
}

////////////////////////////////////////////////////////////////////////////////

OperatorSubtract::OperatorSubtract(const ValueRef& left,
                                   const ValueRef& right)
// Special case
: Operator(left ? left : std::make_shared<Number>(), right)
{ }

float OperatorSubtract::evaluate() {
    return left()->evaluate() - right()->evaluate();
}

////////////////////////////////////////////////////////////////////////////////

OperatorDivide::OperatorDivide(const ValueRef& left,
                               const ValueRef& right)
: Operator(left, right)
{ }

float OperatorDivide::evaluate() {
    auto denom = right()->evaluate();
    if (denom == 0) {
        throw std::runtime_error("Division by zero");
    }
    return left()->evaluate() / denom;
}

////////////////////////////////////////////////////////////////////////////////

OperatorMultiply::OperatorMultiply(const ValueRef& left,
                                   const ValueRef& right)
: Operator(left, right)
{ }

float OperatorMultiply::evaluate() {
    return left()->evaluate() * right()->evaluate();
}

////////////////////////////////////////////////////////////////////////////////

OperatorPower::OperatorPower(const ValueRef& left,
                             const ValueRef& right)
: Operator(left, right)
{ }

float OperatorPower::evaluate() {
    return pow(left()->evaluate(), right()->evaluate());
}
