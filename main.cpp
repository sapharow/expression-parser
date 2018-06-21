#include "evaluator.hpp"

int main(int, char**) {
    
    const char * expression = "3*5*((10/5)+((1+2)+3))*4";
    const float result = Evaluate( expression );
    printf ( "%s = %f\n", expression, result );
    return 0;
}
