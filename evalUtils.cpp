#include "evalUtils.hpp"
#include "operator.hpp"
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
        }
        
        // Parse number
        if (!val) {
            val = parseNumber(expr);
        }
        // Parse optional operator
        while (*expr) {
            switch (*expr) {
                case '+':
                    expr++;
                    val = std::make_shared<OperatorAdd>(val, parseExpression(expr, level));
                    break;
                case '-':
                    expr++;
                    val = std::make_shared<OperatorSubtract>(val, parseExpression(expr, level));
                    break;
                case '/':
                    expr++;
                    val = std::make_shared<OperatorDivide>(val, parseExpression(expr, level));
                    break;
                case '*':
                    expr++;
                    return std::make_shared<OperatorMultiply>(val, parseExpression(expr, level));
                    break;
                case '^':
                    expr++;
                    return std::make_shared<OperatorPower>(val, parseExpression(expr, level));
                    break;
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
