#include "functions.hpp"
#include <math.h>

/**
 * Add here functions to extend functionality
 */
Function::Registry Function::registry = {
    {"sin", [](const ValueRef& arg){ return std::make_shared<SinusFunction>(arg); }}
};

Function::Function(const ValueRef& arg)
: m_Arg(arg)
{
    if (!m_Arg) {
        throw std::runtime_error("Function can not be instantiated w/o value");
    }
}

const ValueRef& Function::arg() const {
    return m_Arg;
}

////////////////////////////////////////////////////////////////////////////////

SinusFunction::SinusFunction(const ValueRef& value)
: Function(value)
{ }

float SinusFunction::evaluate() {
    return sinf(arg()->evaluate());
}
