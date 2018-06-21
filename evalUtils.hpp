#pragma once
#include "types.hpp"

/**
 * Parse number from string
 * @param[in,out] str Pointer to null-terminated string. Function advances it
 *       to the position after parsed number
 */
ValueRef parseNumber(const char*& str);

/**
 * Parse expression recursively
 * @param[in,out] str Pointer to null-terminated string. Function advances it
 *       to the position after parsed expression
 * @param[in] level Bracket level
 */
ValueRef parseExpression(const char*& str, size_t level = 0);
