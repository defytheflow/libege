#pragma once

#include "common.h"

#define BINARY 2
#define OCTAL 8
#define DECIMAL 10
#define HEXADECIMAL 16

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

std::string bin(std::string num, int base);
std::string oct(std::string num, int base);
std::string dec(std::string num, int base);
std::string hex(std::string num, int base);


