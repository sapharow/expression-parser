# What is that? #

This is math expressions parser. It parses expressions into tree of expressions for further evaluation. Currently it provide `float`-based calculations but by extending `Number` class one can substitute float by rational numbers to achieve better precision.

Few assumptions been made:

* Target system has contiguous standard ASCII table (compatible with ISO/IEC 8859-1)
* The input is single-byte characters
* No memory limitations. Building of the evaluation tree is done recursively inside of the brackets which can lead to memory overflow exception at certain nesting level (which is handled though).
* Has reasonable performance avoiding duplicate jobs and extensive memory reallocations
* Target compiler supports C++11 features
* Source code must be built on *nix-family platforms (Ubuntu, MacOSX)
* Source code must be cross-platform and can be easily adopted if needed


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
*   `.` decimal separator
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
* `hypot` Computes hypotenuse of a right-angled triangle whose legs are x and y. Takes two arguments X and Y.

Functions can be nested, e.g. `sin(cos(pi))` is valid input. Functions may have few arguments delimited by `,`, e.g. `hypot(2,3)` is valid input. 

Functions and constants may have same signature. 

### Operation errors ###

* Division by zero is supported. Currently function returns 0.0 and prints message.
* Malformed expressions are correctly treated. Currently function returns 0.0 and prints message.

# How to build #

You have CMake 3.0 or higher installed. Tested with `g++ 4.8, g++ 5.5, g++ 6.3, g++ 7.3` and `clang (LLVM 9.1.0)` compilers.

Checkout repo with `git clone` and the initialise submodules as it depends on Google Test for unit-tests to be run. Then type `git submodule update --recursive --init` to checkout Google Test dependency.

Once checked out type the following:

`mkdir build && cd build && cmake .. && make -j4`
or you can just run `build.sh` and once it builds type `cd build` to get into build directory.

Then you can run unit-tests by typing:
`./unitTests`

and run main app by typing:
`./exPar`