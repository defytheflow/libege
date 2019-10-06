#pragma once

#include "common.h"

#define BINARY 2
#define OCTAL 8
#define DECIMAL 10
#define HEXADECIMAL 16

std::string bin(std::string num, int base);
std::string oct(std::string num, int base);
std::string dec(std::string num, int base);
std::string hex(std::string num, int base);

