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
            string(); // empty string
            string(const char *val); // c-string literal
            string(char *val); // char array
            string(const dtf::string &val); // another dtf::string

        /* Destructor */
            ~string();

        friend std::ostream& operator<<(std::ostream &os, const dtf::string &str);
        friend dtf::string operator+(const dtf::string &other);
        friend bool operator==(const dtf::string &one, const dtf::string &other);
        friend bool operator!=(const dtf::string &one, const dtf::string &other);
    
        public:
        /* Other Methods */
            int length() const;
            int capacity() const;
    };

    int strlen(const char *str); // Returns length of a c-string. 
    void strcpy(char *dest, const char *src, int size); // Copies all chars from 'src' to 'dest'.
}
