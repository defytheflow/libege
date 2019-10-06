#include "common.h"
#include "numconv.h"

using namespace std;

int main(int argc, char *argv[])
{
    string num {"-4"};
    PRINT(bin(num, HEXADECIMAL));
    return 0;
}