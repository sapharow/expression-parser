#include "evalUtils.hpp"
#include "operator.hpp"
#include "function.hpp"
#include "constant.hpp"
#include "number.hpp"

/**
 * Make an assumption here that we are building for platform with
 * contiguous ASCII table
 */
ValueRef parseNumber(const char*& str) {
    const char* originalPtr = str;
    bool bNumerator = true;
    bool bNegative = false;
    
    // negative first component is a flag we didn't encounter digit
    CompoundNumber _number = { -1, 0 };

    size_t size;
    for (size = 0; *str; str++, size++) {
        const int ch = *str - '0';
        if (ch >= 0 && ch < 10) {
            if (_number.first == -1) {
                // Clear flag
                _number.first = 0;
            }
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
                    // We encounter second delimiter. Stop parsing.
                    break;
                }
            } else if (*str == '-' || *str == '+') {
                // Special characters are allowed only as a first symbol of number
                if (!size) {
                    bNegative = *str == '-';
                } else {
                    if (_number.first == -1) {
                        // We encounter second special character. Stop parsing
                        str = originalPtr;
                        return nullptr;
                    }
                    break;
                }
            } else {
                // Unknown character is encountered
                break;
            }
        }
    }
    
    if (_number.first == -1) {
        // We didn't happen to parse even a single digit
        str = originalPtr;
        return nullptr;
    }

    if (bNegative) {
            _number.first = -_number.first;
    }
    return std::make_shared<Number>(_number);
}

/**
 * Parse expression
 * @param[in,out] expr Pointer to null-terminated string with expression.
 *       Function advances pointer to the position after parsed expression
 * @param[in,out] level Bracket level
 * @param[in] prio Operator priority when evaluating right-hand side argument.
 *       When evaluating left-hand side argument, must be equal to -1
 */
static ValueRef parseExpression(const char*& expr, int& level, size_t prio = -1) {
    ValueRef val;

    for (; *expr == ' '; expr++); // Skip spaces

    for (; *expr; ) {
        switch (*expr) {
            case '(':
                expr++;
                level++;
                val = parseExpression(expr, level);
                continue;
                break;
            case ')':
                expr++;
                level--;
                break;
        }
        break;
    }

    if (!val) {
        for (const char* signaturePtr = expr; *signaturePtr; signaturePtr++) {
            int lowerCase = *signaturePtr - 'a';
            int upperCase = *signaturePtr - 'A';
            if ((lowerCase < 0 || lowerCase >= 26) &&
                (upperCase < 0 || upperCase >= 26))
            {
                const size_t signatureSize = signaturePtr - expr;
                std::string signature(expr, signatureSize);
                if (*signaturePtr == '(') {
                    // Function. Check signature
                    auto it = Function::registry.find(signature);
                    if (it != Function::registry.end()) {
                        // Function found
//                        level++;
                        expr += signatureSize;
                        return it->second(parseExpression(expr, level, -1));
                    }
                } else {
                    // Not a function. Parse constants
                    auto it = Constant::registry.find(signature);
                    if (it != Constant::registry.end()) {
                        // Constant found
                        expr += signatureSize;
                        val = it->second;
                    }
                    
                    if (!val) {
                        // Not a constant. Parse number
                        val = parseNumber(expr);
                    }
                    break;
                }
            }
        }
    }
    
    // Parse optional operator
    while (*expr) {
        // Find operator from registry
        auto opIt = Operator::registry.find(*expr);
        if (opIt != Operator::registry.end()) {
            // Found operator
            
            if (prio != (size_t)-1) {
                // Now compare operator's priority over currently parsed one
                if (opIt->second.first <= prio) {
                    return val;
                }
            }
            expr++;
            val = opIt->second.second(val, parseExpression(expr,
                                                           level,
                                                           opIt->second.first));
            continue;
        }
        switch (*expr) {
            case ')':
                if (level <= 0) {
                    throw std::runtime_error("Encountered closing bracket w/o opening one");
                }
                return val;
            case ' ':
                expr++;
                continue;
            case '\0':
                return val;
            default:
                // Unknown symbol
                throw std::runtime_error("Encountered unknown symbol");
                break;
        }
    }
    return val;
}

ValueRef parseExpression(const char*& str) {
    int level = 0;
    auto val = parseExpression(str, level);
    if (level != 0) {
        throw std::runtime_error("Encountered opening bracket w/o closing one");
    }
    return val;
}
