#include "common.h"

void error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}

int count(const std::string &str, char what)
{
    int count {};
    for (const char &ch : str)
    {
        if (ch == what)
            ++count;
    }
    return count;
}