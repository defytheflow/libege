#include <stdio.h>

// A truth table for conjuctions.
int conjuction(int a, int b)
{
    if (a == 1 && b == 1)
        return 1;
    else if (a == 1 && b == 0)
        return 0;
    else if (a == 0 && b == 1)
        return 0;
    else if (a == 0 && b == 0)
        return 0;
}

int disjunction(int a, int b)
{
    if (a == 1 && b == 1)
        return 1;
    else if (a == 1 && b == 0)
        return 1;
    else if (a == 0 && b == 1)
        return 1;
    else if (a == 0 && b == 0)
        return 0;
}

int negation(int a)
{
    if (a == 1)
        return 0;
    else if (a == 0)
        return 1;
}

int main()
{
    printf("%d\n", conjuction(1, 1));
    printf("%d\n", conjuction(0, 0));
    return 0;
}
