#include "common.h"
#include "numconv.h"

using namespace std;

int main(int argc, char *argv[])
{
    string nnums[] = {"-0b1010", "-34", "-0o34", "-0x34"};
    string pnums[] = {"0b1010", "34", "0o34", "0x34"};
    for (int num = 0; num < 4; ++num)
        PRINT(hex(nnums[num]));
    // add prefixes 0b 0o ox when transforming other bases 
    // work on correct and informative exceptions
    return 0;
}