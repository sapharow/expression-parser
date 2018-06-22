#pragma once
#include "value.hpp"
#include "types.hpp"
#include <unordered_map>
#include <functional>
#include <string>

/**
 * Function is abstract interface for any function implementation
 */
class Function : public Value {
public:
    typedef std::function<FunctionRef(const ValueRef&)> Create;
    typedef std::unordered_map<std::string, Create> Registry;

    /**
     * Global functions registry
     */
    static Registry registry;

    /**
     * Create function with argument
     *
     * @param[in] arg Argument
     */
    Function(const ValueRef& arg);

    /**
     * Retrieve argument
     */
    const ValueRef& arg() const;
    
private:
    ValueRef m_Arg;
};


/**
 * Implementations of functions
 * Didn't move to dedicated files to improve readability
 */
class SinusFunction : public Function {
public:
    SinusFunction(const ValueRef&);

    // Overrides from Value
    float evaluate() override;
};

class CosinusFunction : public Function {
public:
    CosinusFunction(const ValueRef&);
    
    // Overrides from Value
    float evaluate() override;
};

class TanFunction : public Function {
public:
    TanFunction(const ValueRef&);
    
    // Overrides from Value
    float evaluate() override;
};

class ATanFunction : public Function {
public:
    ATanFunction(const ValueRef&);
    
    // Overrides from Value
    float evaluate() override;
};

class ASinFunction : public Function {
public:
    ASinFunction(const ValueRef&);
    
    // Overrides from Value
    float evaluate() override;
};

class ACosFunction : public Function {
public:
    ACosFunction(const ValueRef&);
    
    // Overrides from Value
    float evaluate() override;
};
