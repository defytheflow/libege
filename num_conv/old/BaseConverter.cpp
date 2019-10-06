#include "BaseConverter.h"

std::string BaseConverter::bin_to(std::string &bin_num, int base_to)
{
    switch (base_to)
    {
        case OCTAL:
            return bin_to_oct(bin_num);
        case DECIMAL:
            return to_dec(bin_num, BINARY);
        case HEXADECIMAL:
            return bin_to_hex(bin_num);
        default:
            error("Unknown base_to in bin_to method.");
    }
}

std::string BaseConverter::oct_to(std::string &oct_num, int base_to)
{
    switch (base_to)
    {
        case BINARY:
            return oct_to_bin(oct_num);
        case DECIMAL:
            return to_dec(oct_num, OCTAL);
        case HEXADECIMAL:
            return oct_to_hex(oct_num);
    }
}

std::string BaseConverter::dec_to(const std::string &dec_num, int base_to)
{
    // If we have to convert into a Hexadecimal base, overall method for
    // converting from decimal into binary or octal won't work
    if (base_to == HEXADECIMAL)
        return dec_to_hex(dec_num);

    std::string res_num;
    int dec_num_i {std::stoi(dec_num)};
    for (;dec_num_i != 0; dec_num_i /= base_to)
    {
        int remainder {dec_num_i % base_to};
        res_num.push_back(itoc(remainder));
    }
    std::reverse(res_num.begin(), res_num.end());
    return res_num;
}



std::string BaseConverter::to_dec(const std::string &num, int base)
{
    switch(base)
    {
        case BINARY:
            if (!is_binary(num))
                error("Input to 'to_dec()' function is NOT a BINARY number.");
            break;
        case OCTAL:
            if (!is_octal(num))
                error("Input to 'to_dec()' function is NOT an OCTAL number.");
            break;
        case HEXADECIMAL:
            if (!is_hexadecimal(num))
                error("Input to 'to_dec()' function is NOT a HEXADECIMAL number");
            return hex_to_dec(num);
        default:
            error("Unknown input base to 'to_dec() function.");
    }
    int dec_num {};
    std::reverse(num.begin(), num.end());
    for (int i {0}, length {num.length()}; i < length; ++i)
    {
        dec_num += ctoi(num[i]) * std::pow(base, i);
    }
    return std::to_string(dec_num);
}

std::string BaseConverter::bin_to_oct(const std::string &bin_num)
{
    // First convert binary into decimal
    std::string dec_num {to_dec(bin_num, BINARY)};
    // Convert decimal into octal
    return dec_to(dec_num, OCTAL);
}

std::string BaseConverter::oct_to_bin(std::string &oct_num)
{
    std::string bin_num;
    std::map<char, std::string> oct_to_bin_table = {
        {'0', "000"}, {'1', "001"}, {'2', "010"}, {'3', "011"},
        {'4', "100"}, {'5', "101"}, {'6', "110"}, {'7', "111"}
    };
    for (const auto &dig: oct_num)
    {
        bin_num.append(oct_to_bin_table[dig]);
    }
    drop_zeros(bin_num);
    return bin_num;
}

std::string BaseConverter::oct_to_hex(std::string &oct_num)
{
    std::string bin_num {oct_to(oct_num, BINARY)};
    return bin_to(bin_num, HEXADECIMAL);
}

std::string BaseConverter::bin_to_hex(std::string &bin_num)
{
    std::string hex_num;
    std::map<std::string, char> bin_to_hex_table = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };
    pad_zeros(bin_num);
    for (int start {0}, length {bin_num.length()}; start <= length; start += 4)
    {
        hex_num.push_back(bin_to_hex_table[bin_num.substr(start, 4)]);
    }
    return hex_num;
}

std::string BaseConverter::hex_to_bin(const std::string &hex_num)
{
    std::string bin_num;
    std::map<char, std::string> hex_to_bin_table = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
    };
    for (const auto &dig : hex_num)
    {
        bin_num.append(hex_to_bin_table[dig]);
    }
    return bin_num;
}

std::string BaseConverter::dec_to_hex(const std::string &dec_num)
{
    std::string hex_num;
    std::map<int, char> dec_to_hex_table = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
        {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'},
        {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'},
        {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'},
    };
    // Collect all the remainders
    int dec_num_i {std::stoi(dec_num)};
    for (;dec_num_i != 0; dec_num_i /= HEXADECIMAL)
    {
        int remainder {dec_num_i % HEXADECIMAL};
        hex_num.push_back(dec_to_hex_table[remainder]);
    }
    std::reverse(hex_num.begin(), hex_num.end());
    return hex_num;
}

std::string BaseConverter::hex_to_dec(const std::string &hex_num)
{
    int dec_num {};
    std::map<char, std::string> hex_to_dec_table = {
        {'0', "0"}, {'1', "1"}, {'2', "2"}, {'3', "3"},
        {'4', "4"}, {'5', "5"}, {'6', "6"}, {'7', "7"},
        {'8', "8"}, {'9', "9"}, {'A', "10"}, {'B', "11"},
        {'C', "12"}, {'D', "13"}, {'E', "14"}, {'F', "15"},
    };
    std::reverse(hex_num.begin(), hex_num.end());
    for (int i {0}, length = hex_num.length(); i < length; ++i)
    {
        dec_num += stoi(hex_to_dec_table[hex_num[i]]) * std::pow(HEXADECIMAL, i);
    }
    return std::to_string(dec_num);
}

void BaseConverter::pad_zeros(std::string &bin_num)
{
    while (bin_num.length() % 4 != 0)
    {
        bin_num.insert(0, "0");
    }
}

void BaseConverter::drop_zeros(std::string &bin_num)
{
    // If bin_num doesn't start with 0 - we can't drop any zeros.
    if (bin_num[0] != '0') return;

    while (bin_num[0] == '0' || bin_num.length() % 4 != 0)
    {
        bin_num.erase(0, 1);
    }
}

int BaseConverter::ctoi(char ch)
{
    return isdigit(ch) ? ch - '0' : -1;
}

char BaseConverter::itoc(int dig)
{
    switch (dig)
    {
        case 0: case 1: 
        case 2: case 3:
        case 4: case 5: 
        case 6: case 7:
        case 8: case 9:
            return dig + '0';
        default:
            return '\0';
    }
}

bool BaseConverter::is_binary(const std::string &num)
{
    for (const auto &dig : num)
    {
        if (dig != '1' || dig != '0')
            return false;
    }
    return true;
}

bool BaseConverter::is_octal(const std::string &num)
{
    for (const auto &dig : num)
    {
        if (dig == '8' || dig == '9')
            return false;
    }
    return true;
}

bool BaseConverter::is_hexadecimal(const std::string &num)
{
    for (const auto &dig : num)
    {
        switch (dig)
        {
            case '0': case '1': 
            case '2': case '3':
            case '4': case '5': 
            case '6': case '7':
            case '8': case '9': 
            case 'A': case 'B':
            case 'C': case 'D': 
            case 'E': case 'F':
                continue;
            default:
                return false;
        }
    }
    return true;
}