#include "function.hpp"
#include <math.h>

/**
 * Add here functions to extend functionality
 */
Function::Registry Function::registry = {
    {"sin",  [](const ValueRef& arg){ return std::make_shared<SinusFunction>(arg); }},
    {"cos",  [](const ValueRef& arg){ return std::make_shared<CosinusFunction>(arg); }},
    {"tan",  [](const ValueRef& arg){ return std::make_shared<TanFunction>(arg); }},
    {"atan", [](const ValueRef& arg){ return std::make_shared<ATanFunction>(arg); }},
    {"asin", [](const ValueRef& arg){ return std::make_shared<ASinFunction>(arg); }},
    {"acos", [](const ValueRef& arg){ return std::make_shared<ACosFunction>(arg); }},
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

////////////////////////////////////////////////////////////////////////////////

CosinusFunction::CosinusFunction(const ValueRef& value)
: Function(value)
{ }

float CosinusFunction::evaluate() {
    return cosf(arg()->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

TanFunction::TanFunction(const ValueRef& value)
: Function(value)
{ }

float TanFunction::evaluate() {
    return tanf(arg()->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

ATanFunction::ATanFunction(const ValueRef& value)
: Function(value)
{ }

float ATanFunction::evaluate() {
    return atanf(arg()->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

ASinFunction::ASinFunction(const ValueRef& value)
: Function(value)
{ }

float ASinFunction::evaluate() {
    return asinf(arg()->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

ACosFunction::ACosFunction(const ValueRef& value)
: Function(value)
{ }

float ACosFunction::evaluate() {
    return acosf(arg()->evaluate());
}
