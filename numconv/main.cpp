#include "common.h"
#include "numconv.h"

using namespace std;

int main(int argc, char *argv[])
{
    Bin x {"24"}, y {"10"};
    cout << "Addition: " << x << " + " << y << " = " << x + y << endl;
    cout << "Subtraction: " << x << " - " << y << " = " << x - y << endl;
    cout << "Multiplication: " << x << " * " << y << " = " << x * y << endl;
    cout << "Division: " << x << " / " << y << " = " << x / y << endl;
    return 0;
}