#pragma once
#include "common.h"

class Bin
{
    private:
        std::string m_sval;
        int m_ival;

    public:
        /* Constructors */
        Bin();
        Bin(int val);
        Bin(std::string val);

        /* Getters */
        int get_ival() const;
        std::string get_sval() const;

        /* Overloaded Operators */
        Bin operator+(Bin const &other) const;
        Bin operator-(Bin const &other) const;
        Bin operator*(Bin const &other) const;
        Bin operator/(Bin const &other) const;
        friend std::ostream& operator<<(std::ostream &os, const Bin &b);
};

class Oct
{

};

class Hex
{

};

std::string bin(std::string num);
std::string oct(std::string num);
std::string dec(std::string num);
std::string hex(std::string num);