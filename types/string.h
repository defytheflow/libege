#pragma once
#include <iostream>

namespace dtf
{
    class string
    {
        private:
            char *m_buffer;
            int m_capacity;
            int m_length;

        public:
/* Constructors */
            string();
            string(int capacity=0); // empty string
            string(const char *val); // c-string literal
            string(char *val); // char array
            string(const dtf::string &val); // another dtf::string

/* Destructor */
            ~string();

/* Overloaded concatenation ('+=') operator */ 
        dtf::string& operator+=(const char *other);
        dtf::string& operator+=(const dtf::string &other);

/* Overloaded concatenation ('+') operator */ 
        friend dtf::string operator+(const dtf::string &one, const dtf::string &other);
        friend dtf::string operator+(const char *one, const dtf::string &other);
        friend dtf::string operator+(const dtf::string &one, const char *other);

        friend bool operator==(const dtf::string &one, const dtf::string &other);
        friend bool operator!=(const dtf::string &one, const dtf::string &other);

/* Overloaded output ('<<') operator */
        friend std::ostream& operator<<(std::ostream &os, const dtf::string &str);

        public:
/* Other Methods */
            int length() const;
            int capacity() const;
    };

    int strlen(const char *str); // Returns length of a c-string. 
    void strcpy(char *dest, const char *src, int size); // Copies all chars from 'src' to 'dest'.
    void strcat(char *dest, const char *src);
}
