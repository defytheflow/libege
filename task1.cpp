/* Program to solve the first task of the 'EGE' exam.*/
#include "ege_solver.h"

#include <algorithm>
#include <map>
#include <cmath>
#include <cctype>

using namespace std;

class NotDigitError {};

class Converter
{
public:
    /******************************************************************************************** 
     * BINARY -> ( OCTAL | DECIMAL | HEXADECIMAL ) 
     ********************************************************************************************/ 
    static std::string bin_to_oct(std::string bin_num)
    {
        // First convert binary into decimal;
        std::string dec_num {Converter::bin_to_dec(bin_num)};
        // At this point we have converted binary number into decimal
        // Now let's convert it into octal
        std::string oct_num {Converter::dec_to_oct(dec_num)};
        return oct_num;
    }

    static std::string bin_to_dec(std::string bin_num)
    {
        constexpr int base {2};
        int dec_num {0};

        std::reverse(bin_num.begin(), bin_num.end());
        for (int i {0}, length {bin_num.length()}; i < length; ++i)
        {
            dec_num += Converter::ctoi(bin_num[i]) * std::pow(base, i);
        }
        return std::to_string(dec_num);
    }

    static std::string bin_to_hex(std::string bin_num)
    {
        std::string hex_num;
        std::map<std::string, std::string> bin_to_hex_table = {
            {"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"},
            {"0100", "4"}, {"0101", "5"}, {"0110", "6"}, {"0111", "7"},
            {"0100", "8"}, {"0101", "9"}, {"1010", "A"}, {"1011", "B"},
            {"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"},
        };

        pad_zeros(bin_num);
        cout << "Padded zeros: " << bin_num << endl;

        for (int start {0}, end {4}, length = bin_num.length(); start <= length; start += 4)
        {
            hex_num.append(bin_to_hex_table[bin_num.substr(start, end)]);
        }
        return hex_num;
    }
    /******************************************************************************************** 
     * OCTAL -> ( BINARY | DECIMAL | HEXADECIMAL ) 
     ********************************************************************************************/ 
    static std::string oct_to_bin(std::string oct_num)
    {
        std::string bin_num;
        std::map<char, std::string> oct_to_bin_table = {
            {'0', "000"}, {'1', "001"}, {'2', "010"}, {'3', "011"},
            {'4', "100"}, {'5', "101"}, {'6', "110"}, {'7', "111"},
        };
        for (const auto &ch : oct_num)
        {
            bin_num.append(oct_to_bin_table[ch]);
        }
        Converter::drop_zeros(bin_num);
        return bin_num;
    }

    static std::string oct_to_dec(std::string oct_num)
    {
        constexpr int base {8};
        int dec_num {0};
        std::reverse(oct_num.begin(), oct_num.end());
        for (int i {0}, length {oct_num.length()}; i < length; ++i)
        {
            dec_num += Converter::ctoi(oct_num[i]) * std::pow(base, i);
        }
        return std::to_string(dec_num);
    }

    static std::string oct_to_hex(std::string oct_num)
    {
        std::string bin_num {Converter::oct_to_bin(oct_num)};
        Converter::drop_zeros(bin_num);
        return {Converter::bin_to_hex(bin_num)};
    }
    /******************************************************************************************** 
     * DECIMAL -> ( BINARY | OCTAL | HEXADECIMAL ) 
     ********************************************************************************************/ 
    static std::string dec_to_bin(std::string dec_num)
    {
        constexpr int base_into {2};
        std::string bin_num;
        // Collect all the remainders
        int dec_num_i {std::stoi(dec_num)};
        for (;dec_num_i != 0; dec_num_i /= base_into)
        {
            int remainder {dec_num_i % base_into};
            bin_num.append(std::to_string(remainder));
        }
        std::reverse(bin_num.begin(), bin_num.end());
        return bin_num;
    }

    static std::string dec_to_oct(std::string dec_num)
    {
        constexpr int base_into {8};
        std::string oct_num;
        // Collect all the remainders
        int dec_num_i {std::stoi(dec_num)};
        for (;dec_num_i != 0; dec_num_i /= base_into)
        {
            int remainder {dec_num_i % base_into};
            oct_num.append(std::to_string(remainder));
        }
        std::reverse(oct_num.begin(), oct_num.end());
        return oct_num;
    }

    static std::string dec_to_hex(std::string dec_num)
    {
        constexpr int base_into {16};
        std::string hex_num;
        std::map<int, std::string> dec_to_hex_table = {
            {0, "0"}, {1, "1"}, {2, "2"}, {3, "3"},
            {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"},
            {8, "8"}, {9, "9"}, {10, "A"}, {11, "B"},
            {12, "C"}, {13, "D"}, {14, "E"}, {15, "F"},
        };
        // Collect all the remainders
        int dec_num_i {std::stoi(dec_num)};
        for (;dec_num_i != 0; dec_num_i /= base_into)
        {
            int remainder {dec_num_i % base_into};
            hex_num.append(dec_to_hex_table[remainder]);
        }
        std::reverse(hex_num.begin(), hex_num.end());
        return hex_num;
    }
    /******************************************************************************************** 
     * HEXADECIMAL -> ( BINARY | OCTAL | DECIMAL ) 
     ********************************************************************************************/ 
    static std::string hex_to_bin(std::string hex_num)
    {
        std::string bin_num;
        std::map<char, std::string> hex_to_bin_table = {
            {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
            {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
            {'8', "0100"}, {'9', "0101"}, {'A', "1010"}, {'B', "1011"},
            {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
        };
        for (const auto &ch : hex_num)
        {
            bin_num.append(hex_to_bin_table[ch]);
        }
        return bin_num;
    }

    static std::string hex_to_oct(std::string hex_num)
    {
        std::string bin_num {Converter::hex_to_bin(hex_num)};
        return Converter::bin_to_oct(bin_num);
    }

    static std::string hex_to_dec(std::string hex_num)
    {
        constexpr int base {16};
        int dec_num {0};
        std::map<char, std::string> hex_to_dec_table = {
            {'0', "0"}, {'1', "1"}, {'2', "2"}, {'3', "3"},
            {'4', "4"}, {'5', "5"}, {'6', "6"}, {'7', "7"},
            {'8', "8"}, {'9', "9"}, {'A', "10"}, {'B', "11"},
            {'C', "12"}, {'D', "13"}, {'E', "14"}, {'F', "15"},
        };
        std::reverse(hex_num.begin(), hex_num.end());
        for (int i {0}, length = hex_num.length(); i < length; ++i)
        {
            dec_num += stoi(hex_to_dec_table[hex_num[i]]) * std::pow(base, i);
        }
        return std::to_string(dec_num);
    }
private:
    static void pad_zeros(std::string &bin_num)
    {
        while (bin_num.length() % 4 != 0)
        {
            bin_num.insert(0, "0");
        }
    }

    static void drop_zeros(std::string &bin_num)
    {
        if (bin_num[0] != '0') return;

        while (bin_num[0] == '0' || bin_num.length() % 4 != 0)
        {
            bin_num.erase(0, 1);
        }
    }

    static int ctoi(char ch)
    {
        if (std::isdigit(ch)) return ch - '0';
        throw NotDigitError();
    }
};

int main(int argc, char *argv[])
{
    // if (argc != 4)
    //     error("Usage: ./ege_solver <number> <base> <base_into>");

    // int num {std::stoi(argv[1])};
    // int base {std::stoi(argv[2])};
    // int base_into {std::stoi(argv[3])};

    // cout << "Binary " << Converter::dec_to_bin(num) << endl;
    // cout << "Octal " <<Converter::dec_to_oct(num) << endl;
    // cout << "Hexadecimal " <<Converter::dec_to_hex(num) << endl;
    // PRINT(Converter::oct_to_bin(argv[1]));
    
    string num {"AEEF"};

    string bin_num {Converter::hex_to_bin(num)};
    string oct_num {Converter::hex_to_oct(num)};
    string dec_num {Converter::hex_to_dec(num)};

    PRINT(bin_num);
    PRINT(oct_num);
    PRINT(dec_num);
    return 0;
}
