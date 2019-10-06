#include "numconv.h"
#include <gtest/gtest.h>

TEST(Testing_bin_function, Binary_values)
{
    ASSERT_EQ("0", bin("0", BINARY));
    ASSERT_EQ("-10101010", bin("-10101010", BINARY));
    ASSERT_EQ("11110", bin("11110", BINARY));
     
}

TEST(Testing_bin_function, Decimal_values)
{
    ASSERT_EQ("0", bin("0", DECIMAL));
    ASSERT_EQ("11", bin("3", DECIMAL));
    ASSERT_EQ("-100", bin("-4", DECIMAL));
    ASSERT_EQ("-1110", bin("-14", DECIMAL));
    ASSERT_EQ("10101", bin("21", DECIMAL));  
    ASSERT_EQ("10111001", bin("185", DECIMAL));
    ASSERT_EQ("10110011000", bin("1432", DECIMAL));    
}

TEST(Testing_bin_function, Octal_values)
{
    ASSERT_EQ("0", bin("0", OCTAL));
    ASSERT_EQ("11", bin("3", OCTAL));
    ASSERT_EQ("-100", bin("-4", OCTAL));
    ASSERT_EQ("-1100", bin("-14", OCTAL));
    ASSERT_EQ("100101", bin("45", OCTAL));
    ASSERT_EQ("111010101", bin("725", OCTAL));
    ASSERT_EQ("-111010101", bin("-725", OCTAL));
}

TEST(Testing_bin_function, Hexadecimal_values)
{
    ASSERT_EQ("0", bin("0", HEXADECIMAL));
    ASSERT_EQ("11", bin("3", HEXADECIMAL));
    ASSERT_EQ("-100", bin("-4", HEXADECIMAL));
    ASSERT_EQ("-10100", bin("-14", HEXADECIMAL));
    ASSERT_EQ("1000101", bin("45", HEXADECIMAL));
    ASSERT_EQ("11100100101", bin("725", HEXADECIMAL));
    ASSERT_EQ("-10101100", bin("-AC", HEXADECIMAL));
    ASSERT_EQ("1010111000010010", bin("AE12", HEXADECIMAL));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
