#include "evaluator.hpp"

int main(int, char**) {
    
    const char * expression = "54/((2+25)*4)+0.25+sin(12/pi*cos(e))";
    const float result = Evaluate( expression );
    printf ( "%s = %f\n", expression, result );
    return 0;
}
