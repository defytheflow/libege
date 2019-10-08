#include "numconv.h"
#include <gtest/gtest.h>

// bin(std::string) function tests.
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
// oct(std::string) function tests.
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
// dec(std::string) function tests.
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
// to_dec(std::string, int base) function tests.
/******************************************************/
TEST(test_to_dec_function, different_bases)
{
    ASSERT_EQ("0", to_dec("0", 9));
    ASSERT_EQ("-5", to_dec("-12", 3));
    ASSERT_EQ("6", to_dec("12", 4));
    ASSERT_EQ("-7", to_dec("-12", 5));
    ASSERT_EQ("8", to_dec("12", 6));
    ASSERT_EQ("9", to_dec("12", 7));
    ASSERT_EQ("-11", to_dec("-12", 9));
    ASSERT_EQ("13", to_dec("12", 11));
    ASSERT_EQ("-14", to_dec("-12", 12));
    ASSERT_EQ("15", to_dec("12", 13));
    ASSERT_EQ("-16", to_dec("-12", 14));
    ASSERT_EQ("17", to_dec("12", 15));

    ASSERT_EQ("6", to_dec("0110", 2));
    ASSERT_EQ("19", to_dec("23", 8));
    ASSERT_EQ("10", to_dec("10", 10));
    ASSERT_EQ("161", to_dec("A1", 16));
}
/******************************************************/
// dec_to(std::string, int base_to) function tests.
/******************************************************/
TEST(test_dec_to_function, different_bases)
{
    ASSERT_EQ("0", dec_to("0", 9));
    ASSERT_EQ("-110", dec_to("-12", 3));
    ASSERT_EQ("30", dec_to("12", 4));
    ASSERT_EQ("-22", dec_to("-12", 5));
    ASSERT_EQ("20", dec_to("12", 6));
    ASSERT_EQ("15", dec_to("12", 7));
    ASSERT_EQ("-13", dec_to("-12", 9));
    ASSERT_EQ("11", dec_to("12", 11));
    ASSERT_EQ("-10", dec_to("-12", 12));

    ASSERT_EQ("C", dec_to("12", 13));
    ASSERT_EQ("-C", dec_to("-12", 14));
    ASSERT_EQ("C", dec_to("12", 15));

    ASSERT_EQ("0b110", dec_to("6", 2));
    ASSERT_EQ("0o23", dec_to("19", 8));
    ASSERT_EQ("10", dec_to("10", 10));
    ASSERT_EQ("0xA1", dec_to("161", 16));
}
/******************************************************/
// hex(std::string) function tests.
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
// Bin{} class tests.
/******************************************************/
TEST(test_Bin_class, plus_operator)
{
    ASSERT_EQ("0b0", (Bin("0") + Bin("0")).get_sval());
    ASSERT_EQ("0b111101", (Bin("20") + Bin("41")).get_sval());
    ASSERT_EQ("-0b10000101", (Bin("-11") + Bin("-122")).get_sval());
    ASSERT_EQ("0b1101111", (Bin("-11") + Bin("122")).get_sval());
    ASSERT_EQ("0b0", (Bin("111") + Bin("-111")).get_sval());

    ASSERT_EQ("0b0", (Bin(0) + Bin(0)).get_sval());
    ASSERT_EQ("0b111101", (Bin(20) + Bin(41)).get_sval());
    ASSERT_EQ("-0b10000101", (Bin(-11) + Bin(-122)).get_sval());
    ASSERT_EQ("0b1101111", (Bin(-11) + Bin(122)).get_sval());
    ASSERT_EQ("0b0", (Bin(111) + Bin(-111)).get_sval());

    ASSERT_EQ("0b10101", (Bin("0xA") + Bin("0xB")).get_sval());
    ASSERT_EQ("0b1101", (Bin("0o6") + Bin("0o7")).get_sval());
    ASSERT_EQ("0b10100", (Bin("0b1010") + Bin("0b1010")).get_sval());
}
TEST(test_Bin_class, equals_operator)
{
    ASSERT_TRUE(Bin("0") == Bin("0"));
    ASSERT_TRUE(Bin("0b11") == Bin("0b11"));
    ASSERT_TRUE(Bin(24) == Bin(24));
    ASSERT_TRUE(Bin(-31) == Bin(-31));
    ASSERT_TRUE(Bin("0o22") == Bin("0o22"));
    ASSERT_TRUE(Bin("0b0") == Bin(0));
    ASSERT_TRUE(Bin("0x2") == Bin("0o2"));
    ASSERT_TRUE(Bin("0b1010") == Bin(10));
    ASSERT_TRUE(Bin(-3456) == Bin("-3456"));
}
/******************************************************/
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
