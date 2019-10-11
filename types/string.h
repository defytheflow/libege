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
            string(int capacity); // empty string
            string(const char *val); // c-string literal
            string(char *val); // char array
            string(const dtf::string &val); // another dtf::string

/* Destructor */
            ~string();

/* Subscription operator*/
            char operator[](int index) const;

/* Concatenation ('+=') operator */ 
            dtf::string& operator+=(const char *other);
            dtf::string& operator+=(const dtf::string &other);

/* Concatenation ('+') operator */ 
        friend dtf::string operator+(const dtf::string &one, const dtf::string &other);
        friend dtf::string operator+(const char *one, const dtf::string &other);
        friend dtf::string operator+(const dtf::string &one, const char *other);

/* Equal operator */
        friend bool operator==(const dtf::string &one, const dtf::string &other);
        friend bool operator==(const dtf::string &one, const char *other);
        friend bool operator==(const char *one, const dtf::string &other);

/* Not equal operator */
        friend bool operator!=(const dtf::string &one, const dtf::string &other);
        friend bool operator!=(const dtf::string &one, const char *other);
        friend bool operator!=(const char *one, const dtf::string &other);

/* Output ('<<') operator */
        friend std::ostream& operator<<(std::ostream &os, const dtf::string &str);

/* Other Methods */
        public:
            int length() const;
            int capacity() const;
            int count(char what) const;
            dtf::string substr(int begin, int end) const;
    };

/* Public c-string functions. */
    int strlen(const char *str); // Returns length of a c-string. 
    void strcpy(char *dest, const char *src, int size); // Copies all chars from 'src' to 'dest'.
    void strcat(char *dest, const char *src); // Concatenates 'stc' to the end of 'dest' c-strings.
    bool strequal(const char *one, const char *another); // Returns true if chars in both c-strings are equal.
}
