#include "numconv.h"

#define BINARY 2
#define OCTAL 8
#define DECIMAL 10
#define HEXADECIMAL 16

#define POS_BIN_PREFIX "0b"
#define NEG_BIN_PREFIX "-0b"

#define POS_OCT_PREFIX "0o"
#define NEG_OCT_PREFIX "-0o"

#define POS_HEX_PREFIX "0x"
#define NEG_HEX_PREFIX "-0x"

#define BIN_ZERO "0b0"
#define OCT_ZERO "0o0"
#define HEX_ZERO "0x0"

/*****************************************************************
 *          FORWARD DECLARATIONS OF ALL HELPER FUNCTIONS         *
 *****************************************************************/ 

/* Conversion functions cope string value because they
    do prefix manipulation on it. */

// Functions to convert a number to BINARY.
std::string oct_to_bin(std::string oct_num);
std::string dec_to_bin(std::string dec_num_s);
std::string hex_to_bin(std::string hex_num);

// Functions to convert a number to OCTAL.
std::string bin_to_oct(std::string bin_num);
std::string dec_to_oct(std::string dec_num_s);
std::string hex_to_oct(std::string hex_num);

// Functions to convert a number to DECIMAL.
std::string bin_to_dec(std::string bin_num);
std::string oct_to_dec(std::string oct_num);
std::string hex_to_dec(std::string hex_num);

// Functions to convert a number to HEXADECIMAL.
std::string bin_to_hex(std::string bin_num);
std::string oct_to_hex(std::string oct_num);
std::string dec_to_hex(std::string dec_num_s);

// Adds zeros in front of the binary if binary is not a multiple of 4.
std::string pad_zeros(std::string bin_num);
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

// Erases first two characters if number is pos or first three chars if number is neg
std::string rm_prefix(std::string num);

// Returns true if num starts with any of POS_PREFIX.
bool hasprefix(std::string &num);

// Returns true if prefix is '-0b' or '0b'
bool check_bin_prefix(const std::string &num);
// Returns true if prefix is '-0o' or '0o'
bool check_oct_prefix(const std::string &num);
// Returns true if prefix is '-0x' or '0x'
bool check_hex_prefix(const std::string &num);

/*****************************************************************
 *                         EXCEPTIONS                            *
 *****************************************************************/ 

class NotImplementedYet {};
class InvalidLiteral {};

/*****************************************************************
 *               IMPLEMENTATION OF MAIN CLASSES                  *
 *****************************************************************/ 

/* CONSTRUCTORS */

Bin::Bin() {}
// This constructor is used if number to convert is passed as a string
Bin::Bin(std::string val)
{
    m_sval = bin(val);
    m_ival = std::stoi(dec(m_sval));
}
// This constructor is used if number to convert is passed as an int
Bin::Bin(int val)
{
    m_sval = bin(std::to_string(val));
    m_ival = std::stoi(dec(m_sval));
}
/* GETTERS */

int Bin::get_ival() const { return m_ival; }
std::string Bin::get_sval() const { return m_sval; }

/*  OVERLOADED OPERATORS */

bool Bin::operator==(Bin const &other) const
{
    return (m_sval == other.get_sval() && m_ival == other.get_ival());
}

Bin Bin::operator+(Bin const &other) const
{
    char carry {'0'};
    std::string res_sval;
    std::string this_sval {rm_prefix(this->m_sval)};
    std::string other_sval {rm_prefix(other.get_sval())};
    // ---------------------------------------------------------------------
    // Make them eqal in length by padding zeros in front of the lesser one.
    while (other_sval.length() < this_sval.length())
    {
        other_sval.insert(0, "0");
    }
    while (this_sval.length() < other_sval.length())
    {
        this_sval.insert(0, "0");
    }
    // ----------------------------------------------------------------------
    std::reverse(this_sval.begin(), this_sval.end());
    std::reverse(other_sval.begin(), other_sval.end());
    // ----------------------------------------------------------------------
    for (int i = 0, length = this_sval.length(); i < length; ++i)
    {
        if (this_sval[i] == '0' && other_sval[i] == '0')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('0');
                    break;
                case '1':
                    res_sval.push_back('1');
                    carry = '0';
                    break;
            }
        }
        else if (this_sval[i] == '0' && other_sval[i] == '1')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('1');
                    break;
                case '1':
                    res_sval.push_back('0');
                    carry = '1';
                    break;
            }
        }
        else if (this_sval[i] == '1' && other_sval[i] == '0')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('1');
                    break;
                case '1':
                    res_sval.push_back('0');
                    carry = '1';
                    break;
            }
        }
        else if (this_sval[i] == '1' && other_sval[i] == '1')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('0');
                    carry = '1';
                    break;
                case '1':
                    res_sval.push_back('1');
                    carry = '1';
                    break;
            }
        }
    }
    if (carry == '1')
    {
        res_sval.push_back('1');
    }
    // ----------------------------------------------------------------------
    std::reverse(res_sval.begin(), res_sval.end());
    return Bin{POS_BIN_PREFIX  + res_sval};
}

Bin Bin::operator-(Bin const &other) const
{
    std::string val;
    val = bin(std::to_string(this->m_ival - other.get_ival()));
    return Bin{val};
}

Bin Bin::operator*(Bin const &other) const
{
    std::string val;
    val = bin(std::to_string(this->m_ival * other.get_ival()));
    return Bin{val};
}

Bin Bin::operator/(Bin const &other) const
{
    std::string val;
    val = bin(std::to_string(this->m_ival / other.get_ival()));
    return Bin{val};
}

std::ostream& operator<<(std::ostream &os, const Bin &b)
{
    os << b.m_sval;
    return os;
}
/* OTHER METHODS */

// Some tasks ask you to count '1' or '0' in the binary form of a particular number.
int Bin::count(char what) const
{
    int count {};
    std::string sval = rm_prefix(m_sval);
    for (const char &dig : sval)
    {
        if (dig == what)
            ++count;
    }
    return count;
}

/*****************************************************************
 *           DEFINITIONS OF MAIN PUBLIC FUNCTIONS                *
 *****************************************************************/ 

std::string bin(std::string num)
{
    if (isbin(num))
        return num;
    else if (isoct(num))
        return oct_to_bin(num);
    else if (isdec(num))
        return dec_to_bin(num);
    else if (ishex(num))
        return hex_to_bin(num);
    else  
        throw InvalidLiteral();
}


std::string oct(std::string num)
{
    if (isbin(num))
        return bin_to_oct(num);
    else if (isoct(num))
        return num;
    else if (isdec(num))
        return dec_to_oct(num);
    else if (ishex(num))
        return hex_to_oct(num);
    else
        throw InvalidLiteral();
}

std::string dec(std::string num)
{
    if (isbin(num))
        return bin_to_dec(num);
    else if (isoct(num))
        return oct_to_dec(num);
    else if (isdec(num))
        return num;
    else if (ishex(num))
        return hex_to_dec(num);
    else
        throw InvalidLiteral();
}

std::string dec(std::string num, int base)
{
    switch (base)
    {
        case 2:
            return bin(isneg(num) ? NEG_BIN_PREFIX + num.substr(1, num.length()-1) : POS_BIN_PREFIX + num);
        case 8:
            return oct(isneg(num) ? NEG_OCT_PREFIX + num.substr(1, num.length()-1) : POS_OCT_PREFIX + num);
        case 10: // We checl whether the literal user passed is really in base 10 and only then return it.
            return dec(num);
        case 16:
            return hex(isneg(num) ? NEG_HEX_PREFIX + num.substr(1, num.length()-1) : POS_HEX_PREFIX + num);
        case 1: case 3: case 4: case 5:
        case 6: case 7: case 9: case 11:
        case 12: case 13: case 14: case 15:
            any_to_dec(num, base);
        default:
            throw InvalidBase();
    }
}

std::string hex(std::string num)
{
    if (isbin(num))
        return bin_to_hex(num);
    else if (isoct(num))
        return oct_to_hex(num);
    else if (isdec(num))
        return dec_to_hex(num);
    else if (ishex(num))
        return num;
    else
        throw InvalidLiteral();
}

/*****************************************************************
 *          ( OCTAL | DECIMAL | HEXADECIMAL ) -> BINARY          *
 *****************************************************************/ 
 
std::string oct_to_bin(std::string oct_num)
{
    if (oct_num == OCT_ZERO) return BIN_ZERO;
    bool neg {isneg(oct_num)};
    oct_num = rm_prefix(oct_num);

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

    return neg ? NEG_BIN_PREFIX + bin_num : POS_BIN_PREFIX + bin_num;
}

std::string dec_to_bin(std::string dec_num_s)
{
    if (dec_num_s == "0") return BIN_ZERO;
    bool neg {isneg(dec_num_s)};
    std::string bin_num;
    int dec_num_i {};

    if (neg) // Ignore first '-' character when trasformins string into an int
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

    return neg ? NEG_BIN_PREFIX + bin_num : POS_BIN_PREFIX + bin_num;
}

std::string hex_to_bin(std::string hex_num)
{
    if (hex_num == HEX_ZERO) return BIN_ZERO;
    bool neg {isneg(hex_num)};
    hex_num = rm_prefix(hex_num);

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

    return neg ? NEG_BIN_PREFIX + bin_num : POS_BIN_PREFIX + bin_num;
}

/*****************************************************************
 *          ( BINARY | DECIMAL | HEXADECIMAL ) -> OCTAL          *
 *****************************************************************/ 
 
std::string bin_to_oct(std::string bin_num)
{
    if (bin_num == BIN_ZERO) return OCT_ZERO;
    bool neg {isneg(bin_num)};
    bin_num = rm_prefix(bin_num);
    // First convert binary into decimal;
    std::string dec_num_s { neg ? "-" + bin_to_dec(bin_num) : bin_to_dec(bin_num)};
    // Now let's convert decimal to octal
    return dec_to_oct(dec_num_s);
}

std::string dec_to_oct(std::string dec_num_s)
{
    if (dec_num_s == "0") return OCT_ZERO;
    bool neg {isneg(dec_num_s)};
    std::string oct_num;
    // Collect all the remainders
    int dec_num_i {};

    if (neg) // Ignore first '-' character when trasformins string into an int
        dec_num_i = std::stoi(dec_num_s.substr(1, dec_num_s.length()-1));
    else
        dec_num_i = std::stoi(dec_num_s);

    for (;dec_num_i != 0; dec_num_i /= OCTAL)
    {
        int remainder {dec_num_i % OCTAL};
        oct_num.push_back(itoc(remainder));
    }

    std::reverse(oct_num.begin(), oct_num.end());
    return neg ? NEG_OCT_PREFIX + oct_num : POS_OCT_PREFIX + oct_num;
}

std::string hex_to_oct(std::string hex_num)
{
    if (hex_num == HEX_ZERO) return OCT_ZERO;
    bool neg {isneg(hex_num)};
    hex_num = rm_prefix(hex_num);
    std::string dec_num_s {neg ? "-" + hex_to_dec(hex_num) : hex_to_dec(hex_num)};
    return dec_to_oct(dec_num_s);
}

/*****************************************************************
 *          ( BINARY | OCTAL | HEXADECIMAL ) -> DECIMAL          *
 *****************************************************************/ 

std::string bin_to_dec(std::string bin_num)
{
    if (bin_num == BIN_ZERO) return "0";
    bool neg {isneg(bin_num)};
    bin_num = rm_prefix(bin_num);
    int dec_num_i {};
    std::reverse(bin_num.begin(), bin_num.end());
    for (int i {0}, length = bin_num.length(); i < length; ++i)
    {
        dec_num_i += ctoi(bin_num[i]) * std::pow(BINARY, i);
    }
    std::string dec_num_s {std::to_string (dec_num_i)};
    return neg ? "-" + dec_num_s : dec_num_s;
}

std::string oct_to_dec(std::string oct_num)
{
    if (oct_num == OCT_ZERO) return "0";
    bool neg {isneg(oct_num)};
    oct_num = rm_prefix(oct_num);
    int dec_num_i {};
    std::reverse(oct_num.begin(), oct_num.end());
    for (int i {0}, length = oct_num.length(); i < length; ++i)
    {
        dec_num_i += ctoi(oct_num[i]) * std::pow(OCTAL, i);
    }
    std::string dec_num_s {std::to_string (dec_num_i)};
    return neg ? "-" + dec_num_s : dec_num_s;
}

std::string hex_to_dec(std::string hex_num)
{
    if (hex_num == BIN_ZERO) return "0";
    bool neg {isneg(hex_num)};
    hex_num = rm_prefix(hex_num);
    int dec_num_i {};
    std::map<char, std::string> hex_to_dec_table = {
        {'0', "0"}, {'1', "1"}, {'2', "2"}, {'3', "3"},
        {'4', "4"}, {'5', "5"}, {'6', "6"}, {'7', "7"},
        {'8', "8"}, {'9', "9"}, {'A', "10"}, {'B', "11"},
        {'C', "12"}, {'D', "13"}, {'E', "14"}, {'F', "15"},
    };
    std::reverse(hex_num.begin(), hex_num.end());
    for (int i {0}, length = hex_num.length(); i < length; ++i)
    {
        dec_num_i += stoi(hex_to_dec_table[hex_num[i]]) * std::pow(HEXADECIMAL, i);
    }
    std::string dec_num_s {std::to_string (dec_num_i)};
    return neg ? "-" + dec_num_s : dec_num_s;
}

/*****************************************************************
 *          ( BINARY | OCTAL | DECIMAL ) -> HEXADECIMAL          *
 *****************************************************************/ 

std::string bin_to_hex(std::string bin_num)
{
    if (bin_num == BIN_ZERO) return HEX_ZERO;
    bool neg {isneg(bin_num)};
    bin_num = rm_prefix(bin_num);
    std::string hex_num;
    std::map<std::string, char> bin_to_hex_table = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
        {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'},
    };
    bin_num = pad_zeros(bin_num);
    // TODO bug might be in start < length - start <= length
    for (int start {0}, length = bin_num.length(); start < length; start += 4)
    {
        hex_num.push_back(bin_to_hex_table[bin_num.substr(start, 4)]);
    }
    return neg ? NEG_HEX_PREFIX + hex_num : POS_HEX_PREFIX + hex_num;
}

std::string oct_to_hex(std::string oct_num)
{
    if (oct_num == OCT_ZERO) return HEX_ZERO;
    bool neg {isneg(oct_num)};
    oct_num = rm_prefix(oct_num);
    std::string bin_num {neg ? "-" + oct_to_bin(oct_num) : oct_to_bin(oct_num)};
    bin_num = pad_zeros(bin_num);
    return bin_to_hex(bin_num);
}

std::string dec_to_hex(std::string dec_num_s)
{
    if (dec_num_s == "0") return HEX_ZERO;
    bool neg {isneg(dec_num_s)};   
    std::string hex_num;
    std::map<int, char> dec_to_hex_table = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},
        {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'},
        {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'},
        {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'},
    };

    int dec_num_i {};
    if (neg) // Ignore first '-' character when trasformins string into an int
        dec_num_i = std::stoi(dec_num_s.substr(1, dec_num_s.length()-1));
    else
        dec_num_i = std::stoi(dec_num_s);

    // Collect all the remainders
    for (;dec_num_i != 0; dec_num_i /= HEXADECIMAL)
    {
        int remainder {dec_num_i % HEXADECIMAL};
        hex_num.push_back(dec_to_hex_table[remainder]);
    }
    std::reverse(hex_num.begin(), hex_num.end());
    return neg ? NEG_HEX_PREFIX + hex_num : POS_HEX_PREFIX + hex_num;
}

/*****************************************************************
 *                  ARITHMETIC OPERATIONS                        *
 *****************************************************************/ 

/*****************************************************************
 *                     HELPER FUNCTIONS                          *
 *****************************************************************/ 

std::string pad_zeros(std::string bin_num)
{
    if (hasprefix(bin_num)) // 2 because length of '0b' is 2
        bin_num = bin_num.substr(2, bin_num.length() - 1); 
    
    while (bin_num.length() % 4 != 0)
    {
        bin_num.insert(0, "0");
    }
    return bin_num;
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
    // Check for '0b' or '-0b' prefixes
    if (!check_bin_prefix(num))
        return false;

    // 2 or 3 because we skip the '0b' or '-0b' prefixes
    for (int i = isneg(num) ? 3 : 2, length = num.length(); i < length; ++i)
    {
        switch (num[i])
        {
            case '0': case '1': continue;
            default: return false;
        }
    }
    return true;
}

bool isoct(const std::string &num)
{
     // Check for '0o' or '-0o' prefixes
    if (!check_oct_prefix(num))
        return false;

    // 2 or 3 because we skip the '0o' or '-0o' prefixes
    for (int i = isneg(num) ? 3 : 2, length = num.length(); i < length; ++i)
    {
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
     // Check for '0x' or '-0x' prefixes
    if (!check_hex_prefix(num))
        return false;

    // 2 or 3 because we skip the '0x' or '-0x' prefixes
    for (int i = isneg(num) ? 3 : 2, length = num.length(); i < length; ++i)
    {
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

std::string rm_prefix(std::string num)
{
    std::string prefix;
    if (isneg(num))
    {
        prefix = num.substr(0, 3); // '-0b', '-0o', '-0x'
        if (prefix == NEG_BIN_PREFIX || prefix == NEG_OCT_PREFIX || prefix == NEG_HEX_PREFIX)
        {
            for (int _ = 0; _ < 3; ++_)
                num.erase(num.begin());
        }
        return num;
    }   
    else
    {
        prefix = num.substr(0, 2); // '0b', '0o', '0x'
        if (prefix == POS_BIN_PREFIX || prefix == POS_OCT_PREFIX || prefix == POS_HEX_PREFIX)
        {
            for (int _ = 0; _ < 2; ++_)
                num.erase(num.begin());
        }
        return num;
    }
}
// TODO maybe a bug here: 'Why does it check only positive prefixes?'
bool hasprefix(std::string &num)
{
    std::string prefix = num.substr(0, 2);
    return (prefix == POS_BIN_PREFIX || 
            prefix == POS_OCT_PREFIX || 
            prefix == POS_HEX_PREFIX);       
}

bool check_bin_prefix(const std::string &num)
{
    return (num.substr(0, 2) == POS_BIN_PREFIX || num.substr(0, 3) == NEG_BIN_PREFIX);
}

bool check_oct_prefix(const std::string &num)
{
    return (num.substr(0, 2) == POS_OCT_PREFIX || num.substr(0, 3) == NEG_OCT_PREFIX);
}

bool check_hex_prefix(const std::string &num)
{
    return (num.substr(0, 2) == POS_HEX_PREFIX || num.substr(0, 3) == NEG_HEX_PREFIX);
}