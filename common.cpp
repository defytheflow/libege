#include "ege_solver.h"

template <typename T>
void print_vector(std::vector<T> v, std::string sep)
{
    for (auto const &el : v)
        std::cout << el << sep;
    std::cout << std::endl;
}

void error(std::string message)
{
    std::cerr << "[ERROR] " << message << std::endl;
    exit(1);
}