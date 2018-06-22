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
            if (*str == '.') {
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
        if (_number.first > 0) {
            _number.first = -_number.first;
        } else {
            _number.second = -_number.second;
        }
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
static Values parseExpression(const char*& expr, int& level, size_t prio = -1) {
    Values val { nullptr };

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
            case ' ':
                // Skip spaces
                expr++;
                continue;
                break;
            case ',':
                // Some functions may have several arguments
                expr++;
                auto exp = parseExpression(expr, level);
                val.push_back(exp.back());
                continue;
                break;
        }
        break;
    }

    if (!val.back()) {
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
                        expr += signatureSize;
                        // Function may have multiple arguments
                        // Gather all of them
                        return { it->second(parseExpression(expr, level, -1)) };
                    }
                } else {
                    // Not a function. Parse constants
                    auto it = Constant::registry.find(signature);
                    if (it != Constant::registry.end()) {
                        // Constant found
                        expr += signatureSize;
                        val.back() = it->second;
                    }
                    
                    if (!val.back()) {
                        // Not a constant. Parse number
                        val.back() = parseNumber(expr);
                    }
                    break;
                }
            }
        }
    }
    
    // Parse optional operator
    bool bContinueLoop = true;
    while (*expr && bContinueLoop) {
        // Find operator from registry
        auto opIt = Operator::registry.find(*expr);
        if (opIt != Operator::registry.end()) {
            // Found operator
            
            if (prio != (size_t)-1) {
                // Now compare operator's priority over currently parsed one
                if (opIt->second.first <= prio) {
                    break;
                }
            }
            expr++;
            auto rh = parseExpression(expr, level, opIt->second.first);
            if (rh.empty()) {
                throw std::runtime_error("Attempt to use operator with empty right-hand expression");
            }
            val.back() = opIt->second.second(val.back(), rh.back());
            continue;
        }
        switch (*expr) {
            case ')':
                if (level <= 0) {
                    throw std::runtime_error("Encountered closing bracket w/o opening one");
                }
                bContinueLoop = false;
                break;
            case ',': {
                // Some functions may have several arguments
                bContinueLoop = false;
                break;
            }
            case ' ':
                expr++;
                continue;
            case '\0':
                bContinueLoop = false;
                break;
            default:
                // Unknown symbol
                throw std::runtime_error("Encountered unknown symbol");
                break;
        }
    }
    // Remove last nulls
    return val;
}

ValueRef parseExpression(const char*& str) {
    int level = 0;
    auto val = parseExpression(str, level);
    if (*str == ')') {
        level--;
    }
    if (level != 0) {
        throw std::runtime_error("Encountered opening bracket w/o closing one");
    }
    if (!val.empty()) {
        return val.back();
    }
    return nullptr;
}
