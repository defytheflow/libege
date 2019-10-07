#pragma once
#include "common.h"

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

class Binary
{
    private:
        std::string m_val;

    public:
        Binary();
        Binary(int val);
        Binary(std::string val);
        Binary operator+(Binary const &other);
        std::string get_value() const;
        friend std::ostream& operator<<(std::ostream &os, const Binary &b);
};

class Octal
{

};

class Hexadec
{

};

std::string bin(std::string num);
std::string oct(std::string num);
std::string dec(std::string num);
std::string hex(std::string num);


