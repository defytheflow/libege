#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <map>

#define PRINT(x) std::cout << x << std::endl;

// Counts number of 'what' characters in the 'str' string  
int count(const std::string &str, char what);
// Displays message to cerr and terminates the program with 1 exit code.
void error(const std::string &message);