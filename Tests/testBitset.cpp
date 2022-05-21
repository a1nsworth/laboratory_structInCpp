//
// Created by a1nsworth on 5/21/22.
//

#include <gtest/gtest.h>

#include "../lib/lbw/lbw.cpp"

using namespace lbw;

TEST(BitSet_constraction_emptySet, simpleTest) {
    // Arrange and Act
    BitSet a(4);

    // Asserts
    ASSERT_EQ(a.getMaxValue(), 4);
}

TEST(BitSet_constraction_from_vector, simpleTest) {
    // Arrange and Act
    BitSet a = {1,2,3};

    // Asserts
    ASSERT_EQ(a.getData(), 14);
    ASSERT_EQ(a.getMaxValue(), 3);
    ASSERT_EQ(a.getPower(), 3);
}


