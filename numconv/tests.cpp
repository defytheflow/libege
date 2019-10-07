#include "numconv.h"
#include <gtest/gtest.h>

TEST(test_bin_function, binary_values)
{
    ASSERT_EQ("0b0", bin("0b0"));
    ASSERT_EQ("-0b10101010", bin("-0b10101010"));
    ASSERT_EQ("0b11110", bin("0b11110"));
}



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
