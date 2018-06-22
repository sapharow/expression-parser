# What is that? #

This is math expressions parser. It parses expressions into tree of expressions for further evaluation. Currently it provide `float`-based calculations but by rewriting `Number` class one can replace it by rational numbers to achieve better accuracy.

# What is supported? #

### Math operations ###
*   `+`  add
*   `-`  subtract
*   `*`  multiply
*   `/`  divide
*   `^`  power

Priorities (from high to low): 
* `^` has highest priority after brackets
* `*` and `/` have same medium priority
* `+` and `-` have same lowest priority

### Unary operators ###

Numbers can have `-` or `+` symbol in front of them to indicate if they are negative or positive. 
E.g. expression `5*-2` means the same as `5*(-2)` and expression `5*+2` means the same as `5*2`. 

Nevertheless expressions `5*--2` is treated as erroneous as well as `5*++2`.

### Supported symbols ###
* Symbols:
*   `.`, `,` decimal separators
*   `(`, `)` brackets
*   spaces (ignored)

### Supported constants ###
* `pi` PI number 3.141592653589793
* `e` Euler's number

### Supported functions ###
* `sin` Taking sinus() of argument
* `cos` Taking cosinus() of argument
* `tan` Taking tangent() of argument
* `atan` Taking arctanent() of argument
* `asin` Taking arcsinus() of argument
* `acos` Taking arccosinus() of argument

### Operation errors ###

* Division by zero is supported. Currently function returns 0.0 and prints message.
* Malformed expressions are correctly treated. Currently function returns 0.0 and prints message.

# How to build #

You have CMake 3.0 or higher installed. Tested with `g++ 6.3` and `clang (LLVM 9.1.0)`. Compiler must support C++11.

Checkout repo with `git clone` and the initialise submodules as it depends on Google Test for unit-tests to be run. Then type `git submodule update --recursive --init` to checkout Google Test dependency.

Once checked out type the following:

`mkdir build && cd build && cmake .. && make -j4`
or you can just run `build.sh` and once it builds type `cd build` to get into build directory.

Then you can run unit-tests by typing:
`./unitTests`

and run main app by typing:
`./exPar`