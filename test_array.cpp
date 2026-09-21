#include <gtest/gtest.h>
#include "Array.h"

TEST(ArrayTest, Size) {
    Array arr(5);

    EXPECT_EQ(arr.getSize(), 5);
}

TEST(ArrayTest, Access) {
    Array arr(3);

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, OutOfRange) {
    Array arr(3);

    EXPECT_THROW(arr[5], std::out_of_range);
}

TEST(ArrayTest, InvalidSize) {
    EXPECT_THROW(Array arr(0), std::invalid_argument);
    EXPECT_THROW(Array arr(-5), std::invalid_argument);
}