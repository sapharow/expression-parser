#include <gtest/gtest.h>
#include "number.hpp"
#include "types.hpp"
#include "evalUtils.hpp"

TEST(Number, PositiveSingleDigit) {
    NumberRef num;

    std::string textualNumber("1");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(1, num->number().first);
    EXPECT_EQ(0, num->number().second);
    EXPECT_EQ(*str, 0);
}

TEST(Number, PositiveMalformedSingleDigit) {
    NumberRef num;
    
    std::string textualNumber("++1");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_EQ(nullptr, num);
}

TEST(Number, PositiveMultiDigit) {
    NumberRef num;
    
    std::string textualNumber("1235");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(1235, num->number().first);
    EXPECT_EQ(0, num->number().second);
    EXPECT_EQ(*str, 0);
}

TEST(Number, PositiveFrac) {
    NumberRef num;
    
    std::string textualNumber;
    const char* str;

    textualNumber = "123.567";
    str = textualNumber.c_str();
    
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(123, num->number().first);
    EXPECT_EQ(567, num->number().second);
    EXPECT_EQ(*str, 0);

    textualNumber = "123.567.987";
    str = textualNumber.c_str();
    
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(123, num->number().first);
    EXPECT_EQ(567, num->number().second);
    EXPECT_EQ(std::string(str), ".987");

    textualNumber = ".567";
    str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(0, num->number().first);
    EXPECT_EQ(567, num->number().second);
    EXPECT_EQ(*str, 0);

    textualNumber = ".";
    str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_EQ(nullptr, num);
}

TEST(Number, PositiveNull) {
    NumberRef num;
    
    std::string textualNumber("");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_EQ(nullptr, num);
    EXPECT_EQ(*str, 0);
}

TEST(Number, NegativeNull) {
    NumberRef num;
    
    std::string textualNumber("-");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_EQ(nullptr, num);
    EXPECT_EQ(*str, '-');
}

TEST(Number, NegativeSingleDigit) {
    NumberRef num;
    
    std::string textualNumber("-1");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(-1, num->number().first);
    EXPECT_EQ(0, num->number().second);
    EXPECT_EQ(*str, 0);
}

TEST(Number, NegativeMalformedSingleDigit) {
    NumberRef num;
    
    std::string textualNumber("--1");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_EQ(nullptr, num);
}

TEST(Number, NegativeMultiDigit) {
    NumberRef num;
    
    std::string textualNumber("-1234");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(-1234, num->number().first);
    EXPECT_EQ(0, num->number().second);
    EXPECT_EQ(*str, 0);
}

TEST(Number, NegativeFrac) {
    NumberRef num;
    
    std::string textualNumber("-1234.567");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(-1234, num->number().first);
    EXPECT_EQ(567, num->number().second);
    EXPECT_EQ(*str, 0);

    textualNumber = "-.567";
    str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(0, num->number().first);
    EXPECT_EQ(-567, num->number().second);
    EXPECT_EQ(*str, 0);
}

TEST(Number, NaN) {
    NumberRef num;
    
    std::string textualNumber("NaN");
    const char* str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_EQ(nullptr, num);
}

TEST(Number, DigitWithTrailingGarbage) {
    NumberRef num;
    
    std::string textualNumber;
    const char* str;
    
    textualNumber = "1+2";
    str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(1, num->number().first);
    EXPECT_EQ(0, num->number().second);

    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(2, num->number().first);
    EXPECT_EQ(0, num->number().second);
    EXPECT_EQ(*str, 0);

    textualNumber = "1/2";
    str = textualNumber.c_str();
    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_NE(nullptr, num);
    EXPECT_EQ(1, num->number().first);
    EXPECT_EQ(0, num->number().second);

    ASSERT_NO_THROW(num = std::dynamic_pointer_cast<Number>(parseNumber(str)));
    EXPECT_EQ(nullptr, num);
    EXPECT_EQ(std::string(str), "/2");

}
