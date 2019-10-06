#include "common.h"
#include "numconv.h"

using namespace std;

int main(int argc, char *argv[])
{
    Binary x {24};
    Binary y {85};
    PRINT(x);
    PRINT(y);
    PRINT(x + y);
    return 0;
}