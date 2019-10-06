#include "numconv.h"

/*****************************************************************
 *          FORWARD DECLARATIONS OF ALL HELPER FUNCTIONS         *
 *****************************************************************/ 

// Functions to convert a number to BINARY.
std::string oct_to_bin(std::string &oct_num);
std::string dec_to_bin(std::string &dec_num_s);
std::string neg_dec_to_bin(std::string num);
std::string hex_to_bin(std::string &hex_num);

// Functions to convert a number to OCTAL.
std::string bin_to_oct(std::string &bin_num);
std::string dec_to_oct(std::string &dec_num_s);
std::string hex_to_oct(std::string &hex_num);

// Functions to convert a number to DECIMAL.
std::string bin_to_dec(std::string &bin_num);
std::string oct_to_dec(std::string &oct_num);
std::string hex_to_dec(std::string &hex_num);

// Functions to convert a number to HEXADECIMAL.
std::string bin_to_hex(std::string &bin_num);
std::string oct_to_hex(std::string &oct_num);
std::string dec_to_hex(std::string &dec_num_s);

// Adds zeros in front of the binary if binary is not a multiple of 4.
void pad_zeros(std::string &bin_num);
// Removes zeros from the front of the binary if binary is not a multiple of 4.
void drop_zeros(std::string &bin_num);

// Changes '1' characters to '0' characters and vice versa.
void invert_bits(std::string &bin_num);
// Changes '1' char to '0' char and vice versa.
char invert_bit(char bit);

// If ch is a digit, returns it as an integer. Otherwise returns -1.
int ctoi(char ch);
// If dig is a one-character digit, returns it as a char. Otherwise returns '\0'.
char itoc(int dig);

// Returns true if first char of the num is '-'
bool isneg(const std::string &num);

// Returns true if num consists only of '1' and/or '0' characters.
bool isbin(const std::string &num);
// Returns true if num consists only of [0-7] characters.
bool isoct(const std::string &num);
// Returns true id num consists of [0-9] characters.
bool isdec(const std::string &num);
// Returns true if num consists of onlu [0-F] characters.
bool ishex(const std::string &num);

/*****************************************************************
 *                         EXCEPTIONS                            *
 *****************************************************************/ 

class NotImplementedYet {};

/*****************************************************************
 *               IMPLEMENTATION OF MAIN CLASSES                  *
 *****************************************************************/ 
Binary::Binary() {}

// This constructor is used if number to convert is passed as a string
Binary::Binary(std::string val)
{
    m_val = bin(val, DECIMAL);
}

Binary::Binary(int val)
{
    m_val = bin(std::to_string(val), DECIMAL);
}

Binary Binary::operator+(Binary const &other)
{
    PRINT("Inside Binary::operator+");
    throw NotImplementedYet();
}

std::string Binary::get_value() const
{
    return m_val;
}

std::ostream& operator<<(std::ostream &os, const Binary &b)
{
    os << b.m_val;
    return os;
}
/*****************************************************************
 *           DEFINITIONS OF MAIN PUBLIC FUNCTIONS                *
 *****************************************************************/ 

std::string bin(std::string num, int base)
{
    if (num == "0") return "0";
    switch (base)
    {
        case BINARY:
        {
            if (isbin(num))
                return num;
            else
                error("Number " + num + " is not BINARY.");
        }
        case OCTAL:
        {
            if (isoct(num))
                return oct_to_bin(num);
            else
                error("Number " + num + " is not OCTAL.");
        }
        case DECIMAL:
        {
            if (isdec(num))
                return dec_to_bin(num);
            else
                error("Number " + num + " is not DECIMAL.");
        }
        case HEXADECIMAL:
        {
            if (ishex(num))
                return hex_to_bin(num);
            else
               error("Number " + num + " is not HEXADECIMAL.");
        }
        default:
            error("Unknown base.");
    }
}

std::string oct(std::string num, int base)
{
    switch (base)
    {
        case BINARY:
        {
            if (isbin(num))
                return bin_to_oct(num);
            else
                error("Number " + num + " is not BINARY.");
        }
        case OCTAL:
        {
            if (isoct(num))
                return num;
            else
                error("Number " + num + " is not OCTAL.");
        }
        case DECIMAL:
        {
            if (isdec(num))
                return dec_to_oct(num);
            else
                error("Number " + num + " is not DECIMAL.");
        }
        case HEXADECIMAL:
        {
            if (ishex(num))
                return hex_to_oct(num);
            else
               error("Number " + num + " is not HEXADECIMAL.");
        }
        default:
            error("Unknown base.");
    }
}

std::string dec(std::string num, int base)
{
    switch (base)
    {
        case BINARY:
        {
            if (isbin(num))
                return bin_to_dec(num);
            else
                error("Number " + num + " is not BINARY.");
        }
        case OCTAL:
        {
            if (isoct(num))
                return oct_to_dec(num);
            else
                error("Number " + num + " is not OCTAL.");
        }
        case DECIMAL:
        {
            if (isdec(num))
                return num;
            else
                error("Number " + num + " is not DECIMAL.");
        }
        case HEXADECIMAL:
        {
            if (ishex(num))
                return hex_to_dec(num);
            else
               error("Number " + num + " is not HEXADECIMAL.");
        }
        default:
            error("Unknown base.");
    }
}

std::string hex(std::string num, int base)
{
    switch (base)
    {
        case BINARY:
        {
            if (isbin(num))
                return bin_to_hex(num);
            else
                error("Number " + num + " is not BINARY.");
        }
        case OCTAL:
        {
            if (isoct(num))
                return oct_to_hex(num);
            else
                error("Number " + num + " is not OCTAL.");
        }
        case DECIMAL:
        {
            if (isdec(num))
                return dec_to_hex(num);
            else
                error("Number " + num + " is not DECIMAL.");
        }
        case HEXADECIMAL:
        {
            if (ishex(num))
                return num;
            else
               error("Number " + num + " is not HEXADECIMAL.");
        }
        default:
            error("Unknown base.");
    }
}

/*****************************************************************
 *          ( OCTAL | DECIMAL | HEXADECIMAL ) -> BINARY          *
 *****************************************************************/ 
 
std::string oct_to_bin(std::string &oct_num)
{
    std::string bin_num;
    std::map<char, std::string> oct_to_bin_table = {
        {'0', "000"}, {'1', "001"}, {'2', "010"}, {'3', "011"},
        {'4', "100"}, {'5', "101"}, {'6', "110"}, {'7', "111"},
    };
    for (const auto &dig : oct_num)
    {
        bin_num.append(oct_to_bin_table[dig]);
    }
    drop_zeros(bin_num);

    if (isneg(oct_num))
        bin_num.insert(0, "-");

    return bin_num;
}

std::string dec_to_bin(std::string &dec_num_s)
{
    std::string bin_num;
    int dec_num_i {};

    if (isneg(dec_num_s))
        dec_num_i = std::stoi(dec_num_s.substr(1, dec_num_s.length()-1));
    else
        dec_num_i = std::stoi(dec_num_s);
   
    // Collect all the remainders
    for (;dec_num_i != 0; dec_num_i /= BINARY)
    {
        int remainder {dec_num_i % BINARY};
        bin_num.push_back(itoc(remainder));
    }
    std::reverse(bin_num.begin(), bin_num.end());
    drop_zeros(bin_num);
    
    if (isneg(dec_num_s))
        bin_num.insert(0, "-");

    return bin_num;
}

// std::string neg_dec_to_bin(std::string num)
// {
//     //throw NotImplemented("neg_dec_to_bin() has not been implemented yet.");
//     // First we convert it as a positive number into BINARY
//     // we start with 1 because first char is '-'
//     std::string pos_bin_num {bin(num.substr(1, num.length()-1), DECIMAL)};
//     // Then we invert all the bits
//     invert_bits(pos_bin_num);
//     // Now add 1 to the pos_bin_num
//     return bin(std::to_string(std::stoi(dec(pos_bin_num, BINARY)) + 1), DECIMAL);
// }

std::string hex_to_bin(std::string &hex_num)
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
    drop_zeros(bin_num);

    if (isneg(hex_num))
        bin_num.insert(0, "-");

    return bin_num;
}

/*****************************************************************
 *          ( BINARY | DECIMAL | HEXADECIMAL ) -> OCTAL          *
 *****************************************************************/ 
 
std::string bin_to_oct(std::string &bin_num)
{
    // First convert binary into decimal;
    std::string dec_num {bin_to_dec(bin_num)};
    // Now let's convert decimal to octal
    return dec_to_oct(dec_num);
}

std::string dec_to_oct(std::string &dec_num_s)
{
    std::string oct_num;
    // Collect all the remainders
    int dec_num_i {std::stoi(dec_num_s)};
    for (;dec_num_i != 0; dec_num_i /= OCTAL)
    {
        int remainder {dec_num_i % OCTAL};
        oct_num.push_back(itoc(remainder));
    }
    std::reverse(oct_num.begin(), oct_num.end());
    return oct_num;
}

std::string hex_to_oct(std::string &hex_num)
{
    std::string bin_num {hex_to_bin(hex_num)};
    return bin_to_oct(bin_num);
}

/*****************************************************************
 *          ( BINARY | OCTAL | HEXADECIMAL ) -> DECIMAL          *
 *****************************************************************/ 

std::string bin_to_dec(std::string &bin_num)
{
    int dec_num {};
    std::reverse(bin_num.begin(), bin_num.end());
    for (int i {0}, length = bin_num.length(); i < length; ++i)
    {
        dec_num += ctoi(bin_num[i]) * std::pow(BINARY, i);
    }
    return std::to_string(dec_num);
}

std::string oct_to_dec(std::string &oct_num)
{
    int dec_num {};
    std::reverse(oct_num.begin(), oct_num.end());
    for (int i {0}, length = oct_num.length(); i < length; ++i)
    {
        dec_num += ctoi(oct_num[i]) * std::pow(OCTAL, i);
    }
    return std::to_string(dec_num);
}

std::string hex_to_dec(std::string &hex_num)
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

/*****************************************************************
 *          ( BINARY | OCTAL | DECIMAL ) -> HEXADECIMAL          *
 *****************************************************************/ 

std::string bin_to_hex(std::string &bin_num)
{
    std::string hex_num;
    std::map<std::string, char> bin_to_hex_table = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'},
    };
    pad_zeros(bin_num);
    // TODO bug might be in start < length - start <= length
    for (int start {0}, length = bin_num.length(); start < length; start += 4)
    {
        hex_num.push_back(bin_to_hex_table[bin_num.substr(start, 4)]);
    }
    return hex_num;
}

std::string oct_to_hex(std::string &oct_num)
{
    std::string bin_num {oct_to_bin(oct_num)};
    pad_zeros(bin_num);
    return bin_to_hex(bin_num);
}

std::string dec_to_hex(std::string &dec_num_s)
{
    std::string hex_num;
    std::map<int, char> dec_to_hex_table = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
        {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'},
        {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'},
        {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'},
    };
    // Collect all the remainders
    int dec_num_i {std::stoi(dec_num_s)};
    for (;dec_num_i != 0; dec_num_i /= HEXADECIMAL)
    {
        int remainder {dec_num_i % HEXADECIMAL};
        hex_num.push_back(dec_to_hex_table[remainder]);
    }
    std::reverse(hex_num.begin(), hex_num.end());
    return hex_num;
}

/*****************************************************************
 *                  ARITHMETIC OPERATIONS                        *
 *****************************************************************/ 

/*****************************************************************
 *                     HELPER FUNCTIONS                          *
 *****************************************************************/ 

void pad_zeros(std::string &bin_num)
{
    while (bin_num.length() % 4 != 0)
    {
        bin_num.insert(0, "0");
    }
}

void drop_zeros(std::string &bin_num)
{
    // If bin_num doesn't start with 0 - we can't drop any zeros.
    if (bin_num[0] != '0') return;

    while (bin_num[0] == '0') // && bin_num.length() % 4 != 0)
    {
        bin_num.erase(0, 1);
    }
}

void invert_bits(std::string &bin_num)
{
    for (auto &dig: bin_num)
    {
        dig == '0' ? dig = '1' : dig = '0';
    }
}

char invert_bit(char bit)
{
    return bit == '0' ? '1' : '0';
}

int ctoi(char ch)
{
    return isdigit(ch) ? ch - '0' : -1;
}

char itoc(int dig)
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

bool isneg(const std::string &num)
{
    return num[0] == '-';
}

bool isbin(const std::string &num)
{
    for (int i = 0, length = num.length(); i < length; ++i)
    {
        if (i == 0 && num[i] == '-') continue;

        else if (num[i] != '1' && num[i] != '0')
            return false;
    }
    return true;
}

bool isoct(const std::string &num)
{
    for (int i = 0, length = num.length(); i < length; ++i)
    {
        if (i == 0 && num[i] == '-') continue;

        switch(num[i])
        {
            case '0': case '1': 
            case '2': case '3':
            case '4': case '5': 
            case '6': case '7':
                continue;
            default:
                return false;
        }
    }
    return true;
}

bool isdec(const std::string &num)
{
    for (int i {0}, length = num.length(); i < length; ++i)
    {
        if (i == 0 && num[i] == '-') continue;
        else if (!isdigit(num[i])) return false;
    }
    return true;
}

bool ishex(const std::string &num)
{
    for (int i {0}, length = num.length(); i < length; ++i)
    {
        if (i == 0 && num[i] == '-') continue;
        switch (num[i])
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