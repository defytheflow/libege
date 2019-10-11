#include "string.h"

namespace dtf
{

/* Exceptions */
    class IndexError {};

/* Constructors */
    string::string()
    {
        m_capacity = 1;
        m_length = m_capacity - 1;
        m_buffer = new char[m_capacity];
    }

    string::string(int capacity): m_capacity{capacity} 
    {
        m_length = 0;
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

/* Subscription ('[]') operator.*/
    char string::operator[](int index) const
    {
        if (index < 0 || index >= m_length)
            throw IndexError();
        return m_buffer[index];    
    }

/* Concatenation ('+=') operator. */
    dtf::string& string::operator+=(const char *other)
    {
        // Figure out the capacity and length
        int other_length {dtf::strlen(other)};

        m_capacity = m_length + other_length + 1;

        // Fill the temp buffer
        char temp_buffer[m_capacity];
        dtf::strcpy(temp_buffer, m_buffer, m_length);
        dtf::strcat(temp_buffer, other);

        // Update member variables
        delete[] m_buffer;
        m_buffer = new char[m_capacity];
        m_length = m_capacity -1;
        dtf::strcpy(m_buffer, temp_buffer, m_length);
    }

    dtf::string& string::operator+=(const dtf::string &other)
    {
        m_capacity = m_length + other.m_length + 1;

        char temp_buffer[m_capacity];
        dtf::strcpy(temp_buffer, m_buffer, m_length);
        dtf::strcat(temp_buffer, other.m_buffer);

        delete[] m_buffer;
        m_buffer = new char[m_capacity];
        m_length = m_capacity - 1;
        dtf::strcpy(m_buffer, temp_buffer, m_length);
    }

/* FRIENDS - OVERLOADED OPERATORS */

 /* Concatenation ('+') operator */
    dtf::string operator+(const dtf::string &one, const dtf::string &other)
    {
        dtf::string res {one.m_length + other.m_length + 1}; // '\0' is added in the constructor
        res.m_length = one.m_length + other.m_length;
        
        dtf::strcpy(res.m_buffer, one.m_buffer, one.m_length);
        dtf::strcat(res.m_buffer, other.m_buffer);
        return res;
    }

    dtf::string operator+(const char *one, const dtf::string &other)
    {
        int one_length {dtf::strlen(one)};

        dtf::string res {one_length + other.m_length + 1};
        res.m_length = one_length + other.m_length;

        dtf::strcpy(res.m_buffer, one, one_length);
        dtf::strcat(res.m_buffer, other.m_buffer);
        return res;
    }

    dtf::string operator+(const dtf::string &one, const char *other)
    {
        int other_length {dtf::strlen(other)};

        dtf::string res {one.m_length + other_length + 1};
        res.m_length = one.m_length + other_length;

        dtf::strcpy(res.m_buffer, one.m_buffer, one.m_length);
        dtf::strcat(res.m_buffer, other);
        return res;
    }

/* Equal operator ('==') */
    bool operator==(const dtf::string &one, const dtf::string &other) 
    { return dtf::strequal(one.m_buffer, other.m_buffer); }

    bool operator==(const dtf::string &one, const char *other) 
    { return dtf::strequal(one.m_buffer, other); }
    
    bool operator==(const char *one, const dtf::string &other) 
    { return dtf::strequal(one, other.m_buffer); }

/* Not equal ('!=') operator */
    bool operator!=(const dtf::string &one, const dtf::string &other) 
    { return !dtf::strequal(one.m_buffer, other.m_buffer); }

    bool operator!=(const dtf::string &one, const char *other) 
    { return !dtf::strequal(one.m_buffer, other); }
    
    bool operator!=(const char *one, const dtf::string &other) 
    { return !dtf::strequal(one, other.m_buffer); }

/* Output ('<<') operator. */
    std::ostream& operator<<(std::ostream &os, const dtf::string &str)
    {
        os << str.m_buffer;
        return os;
    }

 /* Other methods */
    int string::length() const { return m_length; }
    int string::capacity() const { return m_capacity; }

/* PUBLIC HELPER FUNCTIONS. */

    /* Returns length of a c-string. */
    int strlen(const char *str)
    {
        if (!str) return 0;
        int i{};
        for (char ch = str[i]; ch != '\0'; ++i, ch = str[i]);
        return i;
    }

    /* Copies all chars from 'src' to 'dest' c-string. */
    void strcpy(char *dest, const char *src, int size)
    {
        if (!dest || !src) return;
        int i{};
        for (i = 0; i < size; ++i)
            dest[i] = src[i];
        dest[i] = '\0';
    }

    /* Concatenates 'src' c-string to the 'dest' c-string */
    void strcat(char *dest, const char *src)
    {
        if (!dest || !src) return;
        int i{};
        for (char ch = dest[i]; ch != '\0'; ++i, ch = dest[i]);
        for (int j = 0, length = dtf::strlen(src); j < length; ++j, ++i)
            dest[i] = src[j];
        dest[i] = '\0';
    }

    /* Returns true if both c-strings are equal. */
    bool strequal(const char *one, const char *other)
    {
        int one_length {strlen(one)};
        int other_length {strlen(other)};
        if (one_length != other_length)
            return false;
        int i{};
        for (char ch1 = one[i], ch2 = other[i]; 
            i < one_length; ++i, 
            ch1 = one[i], ch2 = other[i])
        {
            if (one[i] != other[i]) 
                return false;
        }
        return true;
    }   
}





