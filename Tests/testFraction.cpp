//
// Created by a1nsworth on 5/21/22.
//

#include <gtest/gtest.h>

#include "../lib/lbw/lbw.cpp"

using namespace lbw;

TEST(Fraction_construction, notReduces) {
    // Arrange and Act
    Fraction<int> f(11, 4);

    // Asserts
    ASSERT_TRUE(f.getNumenator() == 11);
    ASSERT_TRUE(f.getDenominator() == 4);
}

TEST(Fraction_construction, reduces) {
    // Arrange and Act
    Fraction<int> f(12, 4);

    // Asserts
    ASSERT_TRUE(f.getNumenator() == 3);
    ASSERT_TRUE(f.getDenominator() == 1);
}

TEST(Fraction_construction, numenatorIsNegative) {
    // Arrange and Act
    Fraction<int> f(-11, 4);

    // Asserts
    ASSERT_TRUE(f.getNumenator() == -11);
    ASSERT_TRUE(f.getDenominator() == 4);
}

TEST(Fraction_construction, denominatorIsNegative) {
    // Arrange and Act
    Fraction<int> f(11, -4);

    // Asserts
    ASSERT_TRUE(f.getNumenator() == -11);
    ASSERT_TRUE(f.getDenominator() == 4);
}

TEST(Fraction_construction, allIsNegative) {
    // Arrange and Act
    Fraction<int> f(-11, -4);

    // Asserts
    ASSERT_TRUE(f.getNumenator() == 11);
    ASSERT_TRUE(f.getDenominator() == 4);
}

TEST(Fraction_reduces, notReduces) {
    // Arrange
    Fraction<int> f(11, 4);

    // Act
    f.reduceFraction();

    // Asserts
    ASSERT_TRUE(f.getNumenator() == 11);
    ASSERT_TRUE(f.getDenominator() == 4);
}

TEST(Fraction_reduces, reduces) {
    // Arrange
    Fraction<int> f(12, 4);

    // Act
    f.reduceFraction();

    // Asserts
    ASSERT_TRUE(f.getNumenator() == 3);
    ASSERT_TRUE(f.getDenominator() == 1);
}

TEST(Fraction_reduces, reducesNumenatorIsNegative) {
    // Arrange
    Fraction<int> f(-12, 4);

    // Act
    f.reduceFraction();

    // Asserts
    ASSERT_TRUE(f.getNumenator() == -3);
    ASSERT_TRUE(f.getDenominator() == 1);
}

TEST(Fraction_reduces, reducesDenominatorIsNegative) {
    // Arrange
    Fraction<int> f(12, -4);

    // Act
    f.reduceFraction();

    // Asserts
    ASSERT_TRUE(f.getNumenator() == -3);
    ASSERT_TRUE(f.getDenominator() == 1);
}

TEST(Fraction_reduces, reducesAllIsNegative) {
    // Arrange
    Fraction<int> f(-12, -4);

    // Act
    f.reduceFraction();

    // Asserts
    ASSERT_TRUE(f.getNumenator() == 3);
    ASSERT_TRUE(f.getDenominator() == 1);
}

TEST(Fraction_reduces, reducesNumenatorIsPositive) {
    // Arrange
    Fraction<int> f(-12, 4);

    // Act
    f.reduceFraction();

    // Asserts
    ASSERT_TRUE(f.getNumenator() == -3);
    ASSERT_TRUE(f.getDenominator() == 1);
}

TEST(Fraction_operator_addition, notReducesEqualDenominator) {
    // Arrange
    Fraction<int> f(11,2);
    Fraction<int> d(12,2);

    // Act
    auto res = f + d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 23);
    ASSERT_TRUE(res.getDenominator() == 2);
}

TEST(Fraction_operator_addition, reducesEqualDenominator) {
    // Arrange
    Fraction<int> f(12,2);
    Fraction<int> d(12,2);

    // Act
    auto res = f + d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 12);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_addition, reducesNotEqualDenominator) {
    // Arrange
    Fraction<int> f(10, 5);
    Fraction<int> d(12,2);

    // Act
    auto res = f + d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 8);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_addition, resFractionIsNegative) {
    // Arrange
    Fraction<int> f(8,2);
    Fraction<int> d(-12,2);

    // Act
    auto res = f + d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == -2);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_subtraction, notReducesEqualDenominator) {
    // Arrange
    Fraction<int> f(11,2);
    Fraction<int> d(12,2);

    // Act
    auto res = f - d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == -1);
    ASSERT_TRUE(res.getDenominator() == 2);
}

TEST(Fraction_operator_subtraction, reducesEqualDenominator) {
    // Arrange
    Fraction<int> f(12,2);
    Fraction<int> d(12,2);

    // Act
    auto res = f - d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 0);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_subtraction, reducesNotEqualDenominator) {
    // Arrange
    Fraction<int> f(10, 5);
    Fraction<int> d(12,2);

    // Act
    auto res = f - d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == -4);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_multiplication, reduces) {
    // Arrange
    Fraction<int> f(10, 5);
    Fraction<int> d(12,2);

    // Act
    auto res = f * d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 12);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_multiplication, reducesTwoFracIsNegative) {
    // Arrange
    Fraction<int> f(10, -5);
    Fraction<int> d(-12,2);

    // Act
    auto res = f * d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 12);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_multiplication, oneIsNegative) {
    // Arrange
    Fraction<int> f(-10, 5);
    Fraction<int> d(12,2);

    // Act
    auto res = f * d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == -12);
    ASSERT_TRUE(res.getDenominator() == 1);
}

TEST(Fraction_operator_division, reducesTwoIsPositive) {
    // Arrange
    Fraction<int> f(10, 5);
    Fraction<int> d(12,2);

    // Act
    auto res = f / d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 1);
    ASSERT_TRUE(res.getDenominator() == 3);
}

TEST(Fraction_operator_division, reducesTwoIsNegative) {
    // Arrange
    Fraction<int> f(10, -5);
    Fraction<int> d(-12,2);

    // Act
    auto res = f / d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == 1);
    ASSERT_TRUE(res.getDenominator() == 3);
}

TEST(Fraction_operator_division, reducesOneIsNegative) {
    // Arrange
    Fraction<int> f(10, 5);
    Fraction<int> d(12,-2);

    // Act
    auto res = f / d;

    // Asserts
    ASSERT_TRUE(res.getNumenator() == -1);
    ASSERT_TRUE(res.getDenominator() == 3);
}

