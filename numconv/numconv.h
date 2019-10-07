#pragma once
#include "common.h"

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


