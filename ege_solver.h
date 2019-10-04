#pragma once

#include <iostream>
#include <string>
#include <vector>

#define PRINT(x) cout << x << endl;

// Converts a number from one base into another.
int convert(int num, int base, int base_into);

template <typename T> 
void print_vector(std::vector<T> v, std::string sep);

void error(std::string message);