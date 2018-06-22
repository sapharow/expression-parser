#pragma once
#include <string>
#include "value.hpp"
#include "types.hpp"

typedef std::pair<int64_t, int64_t> CompoundNumber;

/**
 * Number implementation
 */
class Number : public Value {
public:
    Number();
    Number(const CompoundNumber& number);
    
    /**
     * Retrieve number
     */
    const CompoundNumber& number() const;

    // Overrides from Value
    float evaluate() override;

private:
    CompoundNumber m_Number;
};
