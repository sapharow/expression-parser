#include <gtest/gtest.h>
#include "evalUtils.hpp"
#include "types.hpp"
#include "number.hpp"

TEST(Evaluator, SingleNumExpression) {
    std::string expression;
    const char* exPtr;

    expression = "1";
    exPtr = expression.c_str();
    ValueRef value;

    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(1.0, value->evaluate());
    EXPECT_EQ(0, *exPtr);

    expression = "(1)";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(1.0, value->evaluate());
    EXPECT_EQ(0, *exPtr);

    expression = "()";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_EQ(nullptr, value);
    EXPECT_EQ(0, *exPtr);
}

TEST(Evaluator, Expressions) {
    ValueRef value;

    std::string expression;
    const char* exPtr;
    
    expression = "54/2+4";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(31, value->evaluate());

    expression = "1+1";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(2.0, value->evaluate());

    expression = "2+25*4";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(102.0, value->evaluate());

    expression = "(2+25)*4";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(108.0, value->evaluate());

    expression = "54/((2+25)*4)+0.25";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(0.75, value->evaluate());

    expression = "3*5*((10/5)+((1+2)+3))*4";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(480, value->evaluate());
    
    expression = "(1/2*5)+1/4*2";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(3, value->evaluate());

    expression = "3^3";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(27, value->evaluate());

    expression = "-1-1";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(-2, value->evaluate());

    expression = "-(2+2)";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(-4, value->evaluate());

    expression = "5*+2";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(10, value->evaluate());

    expression = "3*-2";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(-6, value->evaluate());

    expression = "5*++2";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
    
    expression = "3*--2";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
}

TEST(Evaluator, MalformedExpressions) {
    ValueRef value;
    
    std::string expression = "1+*)-/2";
    const char* exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
    EXPECT_EQ(nullptr, value);
    
    expression = "1+1qsd";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
    EXPECT_EQ(nullptr, value);

    expression = "1+2)";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
    EXPECT_EQ(nullptr, value);
    
    expression = "(1+2))";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
    EXPECT_EQ(nullptr, value);
    
    expression = "(1+2)+)";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
    EXPECT_EQ(nullptr, value);
    
    expression = "(1+2)+((1";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
    EXPECT_EQ(nullptr, value);
}

TEST(Evaluator, FunctionsExpressions) {
    ValueRef value;
    
    std::string expression = "(pi/2)";
    const char* exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NEAR(1.570796326794897, value->evaluate(), 0.01);
    
    expression = "(( e ) )";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NEAR(2.718281828459045, value->evaluate(), 0.01);

    expression = "12*sin(pi/2)";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NEAR(12, value->evaluate(), 0.000001);

    expression = "12*sin(cos(pi/2))";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NEAR(0, value->evaluate(), 0.000001);

    expression = "12*sin()";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
}

TEST(Evaluator, FunctionsMultiArgExpressions) {
    ValueRef value;
    
    std::string expression;
    const char* exPtr;
    expression = "hypot(1, 2)";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NEAR(2.2360680103302002, value->evaluate(), 0.0001);

    expression = "hypot(1/2,4/8)";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NEAR(0.7071067812, value->evaluate(), 0.000001);

    expression = "hypot((1/2*5)+1/4*2,4/8)";
    exPtr = expression.c_str();
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NEAR(3.0413812651, value->evaluate(), 0.000001);

    expression = "hypot((1/2*5)+1/4*2,4/8,123)";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);

    expression = "hypot((1/2*5)+1/4*2)";
    exPtr = expression.c_str();
    ASSERT_THROW(value = parseExpression(exPtr), std::runtime_error);
}
