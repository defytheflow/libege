#pragma once
#include "../common.h"

class Dec;
class Hex {};

class Bin
{
    private:
        std::string m_pre_sval;
        std::string m_no_pre_sval;
        int m_ival;
        
    public:
        /* Constructors */
        Bin();
        Bin(int val);
        Bin(std::string val);
        Bin(Dec const &d);

        /* Getters */
        int get_ival() const;
        std::string get_sval() const;

        /* Overloaded Operators */
        bool operator==(Bin const &other) const;
        bool operator!=(Bin const &other) const;
        Bin operator+(Bin const &other) const;
        Bin operator-(Bin const &other) const;
        Bin operator*(Bin const &other) const;
        Bin operator/(Bin const &other) const;
        char operator[](int at) const;
        friend std::ostream& operator<<(std::ostream &os, const Bin &b);

        /* Other methods */
        // Returns number of bin digits in m_sval.
        int size() const; 
        int count(char what) const;
};

class Dec
{
    private:
        std::string m_sval;
        int m_ival;
        
    public:
        /* Constructors */
        Dec();
        Dec(int val);
        Dec(std::string val);
        Dec(std::string val, int base);

        /* Getters */
        int get_ival() const;
        std::string get_sval() const;

        /* Overloaded Operators */
        bool operator==(Dec const &other) const;
        bool operator!=(Dec const &other) const;
        Dec operator+(Dec const &other) const;
        Dec operator-(Dec const &other) const;
        Dec operator*(Dec const &other) const;
        Dec operator/(Dec const &other) const;
        friend std::ostream& operator<<(std::ostream &os, const Dec &b);
};

std::string bin(std::string num);
std::string oct(std::string num);
std::string hex(std::string num);
std::string dec(std::string num);

std::string to_dec(std::string num, int base);
std::string dec_to(std::string dec_num, int base_to);
