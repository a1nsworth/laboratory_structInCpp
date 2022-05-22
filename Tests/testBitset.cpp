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
    BitSet a = {1, 2, 3};

    // Asserts
    ASSERT_EQ(a.getData(), 14);
    ASSERT_EQ(a.getMaxValue(), 3);
    ASSERT_EQ(a.getPower(), 3);
}

TEST(BitSet_constraction_from_vector, simpleTest2) {
    // Arrange and Act
    BitSet a({1, 2, 3});

    // Asserts
    ASSERT_EQ(a.getData(), 14);
    ASSERT_EQ(a.getMaxValue(), 3);
    ASSERT_EQ(a.getPower(), 3);
}

TEST(BitSet_insert, onlyOne) {
    // Arrange
    BitSet a = {1, 2, 3, 4};

    // Act
    a.insert(0);

    // Asserts
    ASSERT_EQ(a.getData(), 31);
    ASSERT_EQ(a.getMaxValue(), 4);
    ASSERT_EQ(a.getPower(), 5);
}

TEST(BitSet_insert, twoElmentsAndOneIsReapeat) {
    // Arrange
    BitSet a = {1, 2, 3, 4};

    // Act
    a.insert(0);
    a.insert(1);

    // Asserts
    ASSERT_EQ(a.getData(), 31);
    ASSERT_EQ(a.getMaxValue(), 4);
    ASSERT_EQ(a.getPower(), 5);
}

TEST(BitSet_find, inSet) {
    // Arrange
    BitSet a = {1, 2, 3, 4};

    // Act
    bool isFind = a.find(3);

    // Asserts
    ASSERT_TRUE(isFind);
}

TEST(BitSet_find, notInSet) {
    // Arrange
    BitSet a = {1, 2, 3, 4};

    // Act
    bool isFind = a.find(5);

    // Asserts
    ASSERT_TRUE(!isFind);
}

//TEST(BitSet_find_predicate, firstEven) {
//    // Arrange
//    BitSet a = {2, 3, 4};
//
//    // Act
//    auto element = a.find(0, a.getPower(), [](unsigned x){ return !(x & 1); });
//
//    // Asserts
//    ASSERT_EQ(element, 2);
//}
//
//TEST(BitSet_find_predicate, lastEven) {
//    // Arrange
//    BitSet a = {1, 3, 4};
//
//    // Act
//    auto element = a.find(0, a.getPower(), [](unsigned x){ return !(x & 1); });
//
//    // Asserts
//    ASSERT_EQ(element, 4);
//}
//
//TEST(BitSet_find_predicate, noFind) {
//    // Arrange
//    BitSet a = {1, 3, 7};
//
//    // Act
//    auto element = a.find(0, a.getPower(), [](unsigned x){ return !(x & 1); });
//
//    // Asserts
//    ASSERT_EQ(element, 32);
//}
//
//TEST(BitSet_find_withBorders_predicate, firstEven) {
//    // Arrange
//    BitSet a = {1,2,3,4,5};
//
//    // Act
//    auto element = a.find(1, a.getPower(), [](unsigned x){ return !(x & 1); });
//
//    // Asserts
//    ASSERT_EQ(element, 2);
//}
//
//TEST(BitSet_find_withBorders_predicate, lastEven) {
//    // Arrange
//    BitSet a = {1,9,3,11,5};
//
//    // Act
//    auto element = a.find(1, a.getPower() + 1, [](unsigned x){ return !(x & 1); });
//
//    // Asserts
//    ASSERT_EQ(element, 5);
//}

TEST(BitSet_erase, notInSet) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {1, 2, 3, 4};

    // Act
    a.erase(0);

    // Asserts
    ASSERT_EQ(a, b);
}

TEST(BitSet_erase, first) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {2, 3, 4};

    // Act
    a.erase(1);

    // Asserts
    ASSERT_EQ(a, b);
    ASSERT_TRUE(a.getPower() == b.getPower());
}

TEST(BitSet_erase, last) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {1, 2, 3};

    // Act
    a.erase(4);

    // Asserts
    ASSERT_EQ(a, b);
    ASSERT_TRUE(a.getPower() == b.getPower());
}

TEST(BitSet_isSubset, equalSets) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {1, 2, 3, 4};

    // Act
    bool isSubset = BitSet::isSubset(a, b);

    // Asserts
    ASSERT_TRUE(isSubset);
}

TEST(BitSet_isSubset, notEqualSets) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {5, 6, 7, 8};

    // Act
    bool isSubset = BitSet::isSubset(a, b);

    // Asserts
    ASSERT_TRUE(!isSubset);
}

TEST(BitSet_isSubset, onlyTwoElementsInSet) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {1, 6, 7, 4};

    // Act
    bool isSubset = BitSet::isSubset(a, b);

    // Asserts
    ASSERT_TRUE(!isSubset);
}

TEST(BitSet_isSubset, oneElementAtBegin) {
    // Arrange
    BitSet a = {1};
    BitSet b = {1, 2, 3, 4};

    // Act
    bool isSubset = BitSet::isSubset(a, b);

    // Asserts
    ASSERT_TRUE(isSubset);
}

TEST(BitSet_isSubset, oneElementAtEnd) {
    // Arrange
    BitSet a = {4};
    BitSet b = {1, 2, 3, 4};

    // Act
    bool isSubset = BitSet::isSubset(a, b);

    // Asserts
    ASSERT_TRUE(isSubset);
}

TEST(BitSet_insertions, notEquals) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {5, 6, 7, 8};

    // Act
    auto c = BitSet::insertions(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 0);
    ASSERT_TRUE(c.getData() == 0);
    ASSERT_TRUE(c.getMaxValue() == 0);
}

TEST(BitSet_insertions, oneEqualElemnt) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {4, 6, 7, 8};

    // Act
    auto c = BitSet::insertions(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 1);
    ASSERT_TRUE(c.getData() == 16);
    ASSERT_TRUE(c.getMaxValue() == 4);
}

TEST(BitSet_insertions, twoEqualAtBorders) {
    // Arrange
    BitSet a = {1, 2, 3, 4};
    BitSet b = {1, 6, 7, 4};

    // Act
    auto c = BitSet::insertions(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 2);
    ASSERT_TRUE(c.getData() == 18);
    ASSERT_TRUE(c.getMaxValue() == 4);
}

TEST(BitSet_insertions, twoSetAreEqual) {
    // Arrange
    BitSet a = {0, 1, 2, 3, 4};
    BitSet b = {0, 1, 2, 3, 4};

    // Act
    auto c = BitSet::insertions(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 5);
    ASSERT_TRUE(c.getData() == 31);
    ASSERT_TRUE(c.getMaxValue() == 4);
}

// ----------------
TEST(BitSet_union, notEquals) {
    // Arrange
    BitSet a = {0, 1, 2, 3};
    BitSet b = {4, 5, 6, 7};

    // Act
    auto c = BitSet::union_(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 8);
    ASSERT_TRUE(c.getData() == 255);
    ASSERT_TRUE(c.getMaxValue() == 7);
}

TEST(BitSet_union, oneEqualElemnt) {
    // Arrange
    BitSet a = {0, 1, 2, 3};
    BitSet b = {4, 5, 6, 0};

    // Act
    auto c = BitSet::union_(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 7);
    ASSERT_TRUE(c.getData() == 127);
    ASSERT_TRUE(c.getMaxValue() == 6);
}

TEST(BitSet_union, twoEqualAtBorders) {
    // Arrange
    BitSet a = {0, 1, 2, 3};
    BitSet b = {0, 4, 5, 3};

    // Act
    auto c = BitSet::union_(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 6);
    ASSERT_TRUE(c.getData() == 63);
    ASSERT_TRUE(c.getMaxValue() == 5);
}

TEST(BitSet_union, twoSetAreEqual) {
    // Arrange
    BitSet a = {0, 1, 2, 3, 4};
    BitSet b = {0, 1, 2, 3, 4};

    // Act
    auto c = BitSet::insertions(a, b);

    // Asserts
    ASSERT_TRUE(c.getPower() == 5);
    ASSERT_TRUE(c.getData() == 31);
    ASSERT_TRUE(c.getMaxValue() == 4);
}

TEST(BitSet_addition, full) {
    // Arrange
    BitSet a(31);
    for (size_t i = 0; i <= 31; ++i)
        a.insert(i);

    // Act
    auto c = BitSet::addition(a);

    // Asserts
    ASSERT_TRUE(c.getPower() == 0);
    ASSERT_TRUE(c.getData() == 0);
    ASSERT_TRUE(c.getMaxValue() == 0);
}

TEST(BitSet_addition, onlyOneAtBegin) {
    // Arrange
    BitSet a = {0};

    // Act
    auto c = BitSet::addition(a);

    // Asserts
    ASSERT_TRUE(c.getPower() == 31);
    ASSERT_TRUE(c.getData() == std::numeric_limits<uint32_t>::max() - 1);
    ASSERT_TRUE(c.getMaxValue() == 31);
}

TEST(BitSet_addition, onlyOneAtEnd) {
    // Arrange
    BitSet a(30);
    for (unsigned i = 0; i <= 30; ++i)
        a.insert(i);

    // Act
    auto c = BitSet::addition(a);

    // Asserts
    ASSERT_TRUE(c.getPower() == 1);
    ASSERT_EQ(c.getData(), (std::numeric_limits<uint32_t>::max() + (long long) 1) / 2);
    ASSERT_TRUE(c.getMaxValue() == 31);
}

TEST(BitSet_difference, oneIsUnique) {
    // Arrange
    BitSet a(30);

    // Act
    auto c = BitSet::addition(a);

    // Asserts
    ASSERT_TRUE(c.getPower() == 1);
    ASSERT_EQ(c.getData(), (std::numeric_limits<uint32_t>::max() + (long long) 1) / 2);
    ASSERT_TRUE(c.getMaxValue() == 31);
}