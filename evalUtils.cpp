#include "evalUtils.hpp"
#include "operator.hpp"
#include "functions.hpp"
#include "constants.hpp"
#include "number.hpp"

/**
 * Make an assumption here that we are building for platform with
 * contiguous ASCII table
 */
ValueRef parseNumber(const char*& str) {
    bool bNumerator = true;
    bool bNegative = false;
    CompoundNumber _number = { 0, 0 };
    size_t size;
    for (size = 0; *str; str++, size++) {
        const int ch = *str - '0';
        if (ch >= 0 && ch < 10) {
            if (bNumerator) {
                _number.first *= 10;
                _number.first += ch;
            } else {
                _number.second *= 10;
                _number.second += ch;
            }
        } else {
            if (*str == '.' || *str == ',') {
                if (bNumerator) {
                    bNumerator = false;
                } else {
                    break;
                }
            } else if (!size && *str=='-') {
                bNegative = true;
            } else {
                break;
            }
        }
    }
    
    if ((size && !bNegative) || (size>1 && bNegative)) {
        if (bNegative) {
            _number.first = -_number.first;
        }
        return std::make_shared<Number>(_number);
    }
    if (bNegative) {
        // Return back ptr
        str--;
    }
    return nullptr;
}

static ValueRef parseExpression(const char*& expr, int& level) {
    ValueRef val;
    for (; *expr; expr++) {
        switch (*expr) {
            case '(':
                expr++;
                level++;
                return parseExpression(expr, level);
                break;
            case ')':
                level--;
                return val;
                break;
            case ' ':
                // Skip spaces
                continue;
                break;
            default: {
                // Can be function
                // Find next opening bracket
                for (const char* signaturePtr = expr; *signaturePtr; signaturePtr++) {
                    int lowerCase = *signaturePtr - 'a';
                    int upperCase = *signaturePtr - 'A';
                    if ((lowerCase < 0 || lowerCase >= 26) &&
                        (upperCase < 0 || upperCase >= 26))
                    {
                        if (*signaturePtr == '(') {
                            const size_t signatureSize = signaturePtr - expr;
                            std::string signature(expr, signatureSize);
                            auto it = Function::registry.find(signature);
                            if (it != Function::registry.end()) {
                                // Function found
                                level++;
                                expr += signatureSize+1;
                                return it->second(parseExpression(expr, level));
                            }
                        } else {
                            // Not a function
                            break;
                        }
                    }
                }
            }
        }
        
        // Parse number
        if (!val) {
            val = parseNumber(expr);
            if (!val) {
                // Parse constants
                const char* signaturePtr = expr;
                while (*signaturePtr++) {
                    int lowerCase = *signaturePtr - 'a';
                    int upperCase = *signaturePtr - 'A';
                    if ((lowerCase < 0 || lowerCase >= 26) &&
                        (upperCase < 0 || upperCase >= 26))
                    {
                        const size_t signatureSize = signaturePtr - expr;
                        std::string signature(expr, signatureSize);
                        auto it = Constant::registry.find(signature);
                        if (it != Constant::registry.end()) {
                            // Constant found
                            expr += signatureSize;
                            val = it->second;
                            break;
                        }
                    }
                }

            }
        }
        // Parse optional operator
        while (*expr) {
            // Find operator from registry
            auto opIt = Operator::registry.find(*expr);
            if (opIt != Operator::registry.end()) {
                char e = *expr;
                expr++;
                val = opIt->second(val, parseExpression(expr, level));
                if (e == '*') {
                    // TODO FIXME
                    return val;
                }
                continue;
            }
            switch (*expr) {
                case ')':
                    if (level <= 0) {
                        throw std::runtime_error("Closing bracket w/o opening one");
                    }
                    level--;
                    expr++;
                    return val;
                case ' ':
                    expr++;
                    continue;
                case '\0':
                    return val;
                default:
                    // Unknown symbol
                    throw std::runtime_error("Unknown symbol encountered");
                    break;
            }
        }
        break;
    }
    return val;
}

ValueRef parseExpression(const char*& str) {
    int level = 0;
    return parseExpression(str, level);
}
