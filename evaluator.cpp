#include "evaluator.hpp"
#include "number.hpp"
#include "operator.hpp"
#include "evalUtils.hpp"
#include <algorithm>
#include <vector>

Evaluate::Evaluate(const std::string& expr) {
    // Subdivide evaluation into tree of operators
    try {
        const char* ptr = expr.c_str();
        auto value = parseExpression(ptr);
        if (value) {
            // Compute value of tree
            m_Value = value->evaluate();
        }
    } catch (std::runtime_error& e) {
        printf("Error: %s\n", e.what());
    }
}

Evaluate::operator float() {
    return 0;
}
