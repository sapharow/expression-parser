#pragma once
#include "types.hpp"
#include "value.hpp"

class Operator : public Value {
public:
    Operator(const ValueRef& left,
             const ValueRef& right);
    
    const ValueRef& left() const;
    const ValueRef& right() const;

private:
    ValueRef m_Left;
    ValueRef m_Right;
};

class OperatorAdd : public Operator {
public:
    OperatorAdd(const ValueRef& left,
                const ValueRef& right);
    
    // Overrides from Value
    float evaluate() override;
};

class OperatorSubtract : public Operator {
public:
    OperatorSubtract(const ValueRef& left,
                     const ValueRef& right);
    
    // Overrides from Value
    float evaluate() override;
};

class OperatorDivide : public Operator {
public:
    OperatorDivide(const ValueRef& left,
                   const ValueRef& right);
    
    // Overrides from Value
    float evaluate() override;
};

class OperatorMultiply : public Operator {
public:
    OperatorMultiply(const ValueRef& left,
                     const ValueRef& right);
    
    // Overrides from Value
    float evaluate() override;
};

class OperatorPower : public Operator {
public:
    OperatorPower(const ValueRef& left,
                  const ValueRef& right);
    
    // Overrides from Value
    float evaluate() override;
};
