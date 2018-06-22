CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
PROJECT(ExpressionsParser C CXX)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_library (exParLib
    evalUtils.cpp
    evaluator.cpp
    number.cpp
    number.hpp
    operator.cpp
    function.cpp
    constant.cpp
    )

add_executable (exPar
    main.cpp
    )

add_executable (unitTests
    unitTests/evaluator.cpp
    unitTests/number.cpp
    deps/googletest/googletest/src/gtest-all.cc
    deps/googletest/googletest/src/gtest_main.cc
    )

target_include_directories (exParLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories (exPar    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_include_directories (unitTests PUBLIC
    deps/googletest/googletest/include
    deps/googletest/googletest/
    )

link_directories(
    )

target_link_libraries(
    unitTests
    exParLib
    pthread
    dl
    )

target_link_libraries(
    exPar
    exParLib
    pthread
    dl
    )
