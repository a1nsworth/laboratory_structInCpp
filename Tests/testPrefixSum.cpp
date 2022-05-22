//
// Created by a1nsworth on 5/22/22.
//

#include <gtest/gtest.h>

#include "../lib/lbw/lbw.cpp"

using namespace lbw;

TEST(test_construction_from_vector, simpleTest) {
    // Arrange and Act
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<long long> res = {0, 1, 3, 6, 10};
    PrefixSum a(v);

    // Asserts
    ASSERT_EQ(a.getVector(), res);
}

TEST(test_construction_from_array, simpleTest) {
    // Arrange and Act
    int c[] = {1, 2, 3, 4};
    std::vector<long long> res = {0, 1, 3, 6, 10};
    PrefixSum a(c, 4);

    // Asserts
    ASSERT_EQ(a.getVector(), res);
}

TEST(test_construction_getSum, begin) {
    // Arrange
    PrefixSum a = {0,1,2,3,4};

    // Act
    auto sum = a.getSum(0,1);

    // Asserts
    ASSERT_EQ(sum, 0);
}

TEST(test_construction_getSum, all) {
    // Arrange
    PrefixSum a = {0,1,2,3,4,5};

    // Act
    auto sum = a.getSum();

    // Asserts
    ASSERT_EQ(sum, 15);
}

TEST(test_construction_getSum, oneAtEnd) {
    // Arrange
    PrefixSum a = {0,1,2,3,4,5};

    // Act
    auto sum = a.getSum(5,6);

    // Asserts
    ASSERT_EQ(sum, 5);
}

TEST(test_construction_getSum, atMiddle) {
    // Arrange
    PrefixSum a = {0,1,2,3,4,5};

    // Act
    auto sum = a.getSum(2,4);

    // Asserts
    ASSERT_EQ(sum, 5);
}

TEST(test_construction_getSum, all2) {
    // Arrange
    PrefixSum a = {0,1,2,3,4,5};

    // Act
    auto sum = a.getSum(0,6);

    // Asserts
    ASSERT_EQ(sum, 15);
}

TEST(test_construction_set, replaceFirst) {
    // Arrange
    PrefixSum a = {0,1,2,3,4,5};

    // Act
    a.set(0, 1);
    PrefixSum res = {1,1,2,3,4,5};

    // Asserts
    ASSERT_EQ(a.getVector(), res.getVector());
}

TEST(test_construction_set, replaceLast) {
    // Arrange
    PrefixSum a = {0,1,2,3,4,5};

    // Act
    a.set(5, 6);
    PrefixSum res = {0,1,2,3,4,6};

    // Asserts
    ASSERT_EQ(a.getVector(), res.getVector());
}

TEST(test_construction_set, firstAndLast) {
    // Arrange
    PrefixSum a = {0,1,2,3,4,5};

    // Act
    a.set(5, 6);
    a.set(0, 10);
    PrefixSum res = {10,1,2,3,4,6};

    // Asserts
    ASSERT_EQ(a.getVector(), res.getVector());
}

TEST(test_construction_set, allElements) {
    // Arrange
    PrefixSum a = {0,1,2,3};

    // Act
    a.set(0, 3);
    a.set(1, 4);
    a.set(2, 5);
    a.set(3, 6);
    PrefixSum res = {3,4,5,6};

    // Asserts
    ASSERT_EQ(a.getVector(), res.getVector());
}