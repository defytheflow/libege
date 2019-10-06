#pragma once

#include "common.h"

#define BINARY 2
#define OCTAL 8
#define DECIMAL 10
#define HEXADECIMAL 16

class BaseConverter
{
public:
    // Converts BINARY number to (OCTAL | DECIMAL | HEXADECIMAL)
    std::string bin_to(std::string &bin_num, int base_to);

    // Converts DECIMAL number to (BINARY | OCTAL | HEXADECIMAL | TRIPLE)
    std::string dec_to(const std::string &dec_num, int base_to);

    std::string oct_to(std::string &oct_num, int base_to);


    // Converts (BINARY | OCTAL | HEXADECIMAL) number to DECIMAL
    std::string to_dec(const std::string &num, int base);

    std::string to_bin(const std::string num, int base);

    std::string hex_to_bin(const std::string &hex_num);

private:
    std::string dec_to_hex(const std::string &dec_num);

    std::string hex_to_dec(const std::string &hex_num);

    std::string bin_to_oct(const std::string &bin_num);

    std::string bin_to_hex(std::string &bin_num);

    std::string oct_to_bin(std::string &oct_num);

    std::string oct_to_hex(std::string &oct_num);


/* HELPER Methods */
private: 
    
    // Adds zeros in front of the binary if binary is not a multiple of 4.
    void pad_zeros(std::string &bin_num);
    
    // Removes zeros from the front of the binary if binary is not a multiple of 4.
    void drop_zeros(std::string &bin_num);
    
    // If ch is a digit, returns it as an integer. Otherwise returns -1.
    int ctoi(char ch);

    // If dig is a one-character digit, returns it as a char. Otherwise returns '\0'.
    char itoc(int dig);
    
    // Returns true if num consists only of '1' and/or '0' characters.
    bool is_binary(const std::string &num);
    // Returns true if num consists only of [0-7] characters.
    bool is_octal(const std::string &num);
    // Returns true if num consists of onlu [0-F] characters.
    bool is_hexadecimal(const std::string &num);
};