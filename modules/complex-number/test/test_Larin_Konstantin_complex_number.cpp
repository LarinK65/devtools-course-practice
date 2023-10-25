// Copyright 2023 Larin Konstantin
#include <gtest/gtest.h>

#include "include/complex_number.h"

TEST(Larin_Konstantin_ComplexNumberTest, equal_to_itself) {
    ComplexNumber num(0.5, 11);

    ASSERT_TRUE(num == num);
}

TEST(Larin_Konstantin_ComplexNumberTest, difference_is_zero) {
    ComplexNumber num(0.5, 11);

    ASSERT_TRUE(num - num == ComplexNumber{});
}

TEST(Larin_Konstantin_ComplexNumberTest, sum) {
    ComplexNumber a(0.5, 11);
    ComplexNumber b(1.1, 2.2);

    auto result = a + b;

    ASSERT_DOUBLE_EQ(result.getRe(), 1.6);
    ASSERT_DOUBLE_EQ(result.getIm(), 13.2);
}

TEST(Larin_Konstantin_ComplexNumberTest, multiply_to_one) {
    ComplexNumber a(0.5, 11);
    ComplexNumber b(1, 0);

    ASSERT_TRUE(a * b == a);
}

TEST(Larin_Konstantin_ComplexNumberTest, multiply_to_zero) {
    ComplexNumber a(0.5, 11);
    ComplexNumber b(0, 0);

    ASSERT_TRUE(a * b == ComplexNumber{});
}

TEST(Larin_Konstantin_ComplexNumberTest, add_zero) {
    ComplexNumber a(0.5, 11);
    ComplexNumber b(0, 0);

    ASSERT_TRUE(a + b == a);
}
