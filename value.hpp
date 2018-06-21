#pragma once

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
