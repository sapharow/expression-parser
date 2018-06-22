#include "function.hpp"
#include <math.h>

/**
 * Add here functions to extend functionality
 */
Function::Registry Function::registry = {
    {"sin",  [](const Values& arg){ return std::make_shared<SinusFunction>(arg); }},
    {"cos",  [](const Values& arg){ return std::make_shared<CosinusFunction>(arg); }},
    {"tan",  [](const Values& arg){ return std::make_shared<TanFunction>(arg); }},
    {"atan", [](const Values& arg){ return std::make_shared<ATanFunction>(arg); }},
    {"asin", [](const Values& arg){ return std::make_shared<ASinFunction>(arg); }},
    {"acos", [](const Values& arg){ return std::make_shared<ACosFunction>(arg); }},
    {"hypot", [](const Values& arg){ return std::make_shared<HypotFunction>(arg); }},
};

Function::Function(const Values& arg, size_t numArgs)
: m_Arg(arg)
{
    if (m_Arg.empty()) {
        throw std::runtime_error("Function can not be instantiated w/o argument");
    }
    if (m_Arg.size() != numArgs) {
        throw std::runtime_error("Function has incorrect number of arguments");
    }
    for (auto& arg : m_Arg) {
        if (!arg) {
            throw std::runtime_error("Function can not be instantiated with empty argument");
        }
    }
}

const Values& Function::arg() const {
    return m_Arg;
}

////////////////////////////////////////////////////////////////////////////////

SinusFunction::SinusFunction(const Values& value)
: Function(value, 1)
{
}

float SinusFunction::evaluate() {
    return sinf(arg()[0]->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

CosinusFunction::CosinusFunction(const Values& value)
: Function(value, 1)
{
}

float CosinusFunction::evaluate() {
    return cosf(arg()[0]->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

TanFunction::TanFunction(const Values& value)
: Function(value, 1)
{
}

float TanFunction::evaluate() {
    return tanf(arg()[0]->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

ATanFunction::ATanFunction(const Values& value)
: Function(value, 1)
{
}

float ATanFunction::evaluate() {
    return atanf(arg()[0]->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

ASinFunction::ASinFunction(const Values& value)
: Function(value, 1)
{
}

float ASinFunction::evaluate() {
    return asinf(arg()[0]->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

ACosFunction::ACosFunction(const Values& value)
: Function(value, 1)
{
}

float ACosFunction::evaluate() {
    return acosf(arg()[0]->evaluate());
}

////////////////////////////////////////////////////////////////////////////////

HypotFunction::HypotFunction(const Values& value)
: Function(value, 2)
{
}

float HypotFunction::evaluate() {
    return hypot(arg()[0]->evaluate(), arg()[1]->evaluate());
}
