#pragma once
#include <string>
#include <unordered_map>
#include "types.hpp"

/**
 * Evaluator supports the following:
 * Math operations:
 *   +  add
 *   -  subtract
 *   *  multiply
 *   /  divide
 *   ^  power
 *
 * Symbols:
 *   ., decimal separators
 *   () brackets
 *      spaces (ignored)
 *
 * Extra:
 */
class Evaluate {
public:
    /**
     * Create evaluator with expression to evaluate
     * @param[in] expr Expression to evaluate
     */
    Evaluate(const std::string& expr);
    
    /**
     * Retrieve expression value
     */
    operator float();

private:
    
    float m_Value = 0;
    OperatorRef m_Root;
};
