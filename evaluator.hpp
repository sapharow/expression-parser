#pragma once
#include <string>
#include <unordered_map>
#include "types.hpp"

class Evaluate {
public:
    /**
     * Create evaluator with expression to evaluate. Supported non-numerical
     * symbols are:
     * +  add
     * -  subtract
     * *  multiply
     * /  divide
     * ^  power
     * ., decimal separator
     * () brackets
     *
     * Implementation notes:
     * > Spaces are supported
     * 
     *
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
