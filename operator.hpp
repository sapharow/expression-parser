#pragma once
#include "types.hpp"
#include "value.hpp"
#include <unordered_map>
#include <functional>

class Operator : public Value {
public:
    typedef std::function<OperatorRef(const ValueRef&, const ValueRef&)> Create;
    typedef std::unordered_map<char, Create> Registry;

    /**
     * Global operators registry
     */
    static Registry registry;

    /**
     * Create operator with two arguments
     * @param[in] left Left argument
     * @param[in] right Right argument
     */
    Operator(const ValueRef& left,
             const ValueRef& right);
    
    /**
     * Retrieve operator left argument
     */
    const ValueRef& left() const;
    
    /**
     * Retrieve operator right argument
     */
    const ValueRef& right() const;

private:
    ValueRef m_Left;
    ValueRef m_Right;
};

/**
 * Implementations of operators
 * Didn't move to dedicated files to improve readability
 */
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
