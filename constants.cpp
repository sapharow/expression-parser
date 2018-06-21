#include "constants.hpp"
#include "number.hpp"
#include <math.h>

/**
 * Add here constants to extend functionality
 */
Constant::Registry Constant::registry = {
    {"pi", std::make_shared<Number>(std::make_pair(3, 141592653589793)) }
};
