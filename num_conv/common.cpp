#include "common.h"

void error(std::string message)
{
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}