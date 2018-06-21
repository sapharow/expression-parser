#include "number.hpp"
#include <math.h>

Number::Number()
: m_Number(0,0)
{ }

Number::Number(const CompoundNumber& number)
: m_Number(number)
{ }

const CompoundNumber& Number::number() const {
    return m_Number;
}

float Number::evaluate() {
    size_t nDigits = floor(log10f(m_Number.second)) + 1;
    return (float)m_Number.first + (float)m_Number.second / pow(10, nDigits);
}
