#include <gtest/gtest.h>
#include "evalUtils.hpp"
#include "types.hpp"
#include "number.hpp"

TEST(Evaluator, SingleNumExpression) {
    std::string expression = "1";
    const char* exPtr = expression.c_str();
    ValueRef value;
    ASSERT_NO_THROW(value = parseExpression(exPtr));
    EXPECT_NE(nullptr, value);
    EXPECT_EQ(1.0, value->evaluate());
}

TEST(Evaluator, Expressions) {
    ValueRef value;

    std::string expression = "1+1";
    const char* exPtr = expression.c_str();
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
}

TEST(Evaluator, MalformedExpressions) {
    ValueRef value;
    
    std::string expression = "1+*)-/2";
    const char* exPtr = expression.c_str();
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
}
