#include "numconv.h"
#include <gtest/gtest.h>

// bin() function tests.
/******************************************************/
TEST(test_bin_function, binary_values)
{
    ASSERT_EQ("0b0", bin("0b0"));
    ASSERT_EQ("-0b10101010", bin("-0b10101010"));
    ASSERT_EQ("0b11110", bin("0b11110"));
}
TEST(test_bin_function, octal_values)
{
    ASSERT_EQ("0b0", bin("0o0"));
    ASSERT_EQ("-0b100101", bin("-0o45"));
    ASSERT_EQ("0b111", bin("0o7"));
}
TEST(test_bin_function, decimal_values)
{
    ASSERT_EQ("0b0", bin("0"));
    ASSERT_EQ("-0b101101", bin("-45"));
    ASSERT_EQ("0b111", bin("7"));
}
TEST(test_bin_function, hexadecimal_values)
{
    ASSERT_EQ("0b0", bin("0x0"));
    ASSERT_EQ("-0b1001010", bin("-0x4A"));
    ASSERT_EQ("0b110001", bin("0x31"));
}
/******************************************************/
// oct() function tests.
/******************************************************/
TEST(test_oct_function, binary_values)
{
    ASSERT_EQ("0o0", oct("0b0"));
    ASSERT_EQ("-0o52", oct("-0b101010"));
    ASSERT_EQ("0o377", oct("0b11111111"));
}
TEST(test_oct_function, octal_values)
{
    ASSERT_EQ("0o0", oct("0o0"));
    ASSERT_EQ("-0o123", oct("-0o123"));
    ASSERT_EQ("0o11111111", oct("0o11111111"));
}
TEST(test_oct_function, decimal_values)
{
    ASSERT_EQ("0o0", oct("0"));
    ASSERT_EQ("-0o173", oct("-123"));
    ASSERT_EQ("0o17", oct("15"));
}
TEST(test_oct_function, hexadecimal_values)
{
    ASSERT_EQ("0o0", oct("0x0"));
    ASSERT_EQ("-0o104", oct("-0x44"));
    ASSERT_EQ("0o16", oct("0xE"));
}
/******************************************************/
// dec() function tests.
/******************************************************/
TEST(test_dec_function, binary_values)
{
    ASSERT_EQ("0", dec("0b0"));
    ASSERT_EQ("-255", dec("-0b11111111"));
    ASSERT_EQ("10", dec("0b1010"));
}
TEST(test_dec_function, octal_values)
{
    ASSERT_EQ("0", dec("0o0"));
    ASSERT_EQ("-59", dec("-0o73"));
    ASSERT_EQ("112", dec("0o160"));
}
TEST(test_dec_function, decimal_values)
{
    ASSERT_EQ("0", dec("0"));
    ASSERT_EQ("-345", dec("-345"));
    ASSERT_EQ("10230", dec("10230"));
}
TEST(test_dec_function, hexadecimal_values)
{
    ASSERT_EQ("0", dec("0x0"));
    ASSERT_EQ("-228", dec("-0xE4"));
    ASSERT_EQ("308", dec("0x134"));
}
/******************************************************/
// hex() function tests.
/******************************************************/
TEST(test_hex_function, binary_values)
{
    ASSERT_EQ("0x0", hex("0b0"));
    ASSERT_EQ("-0xB8", hex("-0b10111000"));
    ASSERT_EQ("0x1F", hex("0b11111"));
}
TEST(test_hex_function, octal_values)
{
    ASSERT_EQ("0x0", hex("0o0"));
    ASSERT_EQ("-0x14", hex("-0o24"));
    ASSERT_EQ("0x3A", hex("0o072"));
}
TEST(test_hex_function, decimal_values)
{
    ASSERT_EQ("0x0", hex("0"));
    ASSERT_EQ("-0x80", hex("-128"));
    ASSERT_EQ("0x40", hex("064"));
}
TEST(test_hex_function, hexadecimal_values)
{
    ASSERT_EQ("0x0", hex("0x0"));
    ASSERT_EQ("-0xAE324", hex("-0xAE324"));
    ASSERT_EQ("0x12345", hex("0x12345"));
}   
/******************************************************/

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
