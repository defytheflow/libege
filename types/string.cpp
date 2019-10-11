#include "string.h"

namespace dtf
{
    /* Constructors */
    string::string() 
    {
        m_length = 0;
        m_capacity = 1;
        m_buffer = new char[m_capacity];
    };
    string::string(const char *val)
    {
        m_length = dtf::strlen(val); 
        m_capacity = m_length + 1; // + '\0'
        m_buffer = new char[m_capacity];
        dtf::strcpy(m_buffer, val, m_length);
    }
    /* Destructor */
    string::~string()
    {
        delete[] m_buffer;
    }
    /* Other methods */
    int string::length() const { return m_length; }
    int string::capacity() const { return m_capacity; }

    /* Overloaded operators */
    std::ostream& operator<<(std::ostream &os, const dtf::string &str)
    {
        os << str.m_buffer;
        return os;
    }

    /* Returns length of a c-string. */
    int strlen(const char *str)
    {
        if (!str) return 0;
        int i{}, length{};
        for (char ch = str[i]; ch != '\0'; ++i, ch = str[i])
            ++length;
        return length;
    }

    /* Copies all chars from 'src' to 'dest' c-string. */
    void strcpy(char *dest, const char *src, int size)
    {
        if (!dest || !src) return;
        unsigned i{};
        for (i = 0; i < size; ++i)
            dest[i] = src[i];
        dest[i] = '\0';
    }   
}





