#pragma once
#include <vector>
#include "types.hpp"

typedef std::vector<ValueRef> Values;

/**
 * Generic value which can be evaluated
 */
class Value {
public:
    virtual ~Value() = default;
    
    /**
     * Evaluate value
     */
    virtual float evaluate() = 0;
};
