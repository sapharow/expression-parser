#pragma once
#include "value.hpp"
#include "types.hpp"
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

/**
 * Function is abstract interface for any function implementation
 */
class Function : public Value {
public:
    typedef std::function<FunctionRef(const Values&)> Create;
    typedef std::unordered_map<std::string, Create> Registry;

    /**
     * Global functions registry
     */
    static Registry registry;

    /**
     * Create function with argument
     *
     * @param[in] arg Argument
     * @param[in] numArgs Expected number of arguments
     */
    Function(const Values& arg, size_t numArgs);

    /**
     * Retrieve argument
     */
    const Values& arg() const;
    
private:
    Values m_Arg;
};


/**
 * Implementations of functions
 * Didn't move to dedicated files to improve readability
 */
class SinusFunction : public Function {
public:
    SinusFunction(const Values&);

    // Overrides from Value
    float evaluate() override;
};

class CosinusFunction : public Function {
public:
    CosinusFunction(const Values&);
    
    // Overrides from Value
    float evaluate() override;
};

class TanFunction : public Function {
public:
    TanFunction(const Values&);
    
    // Overrides from Value
    float evaluate() override;
};

class ATanFunction : public Function {
public:
    ATanFunction(const Values&);
    
    // Overrides from Value
    float evaluate() override;
};

class ASinFunction : public Function {
public:
    ASinFunction(const Values&);
    
    // Overrides from Value
    float evaluate() override;
};

class ACosFunction : public Function {
public:
    ACosFunction(const Values&);
    
    // Overrides from Value
    float evaluate() override;
};

class HypotFunction : public Function {
public:
    HypotFunction(const Values&);
    
    // Overrides from Value
    float evaluate() override;
};
