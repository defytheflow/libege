#include "../common.h"
#include "truthtab.h"

using namespace std;

// void precedence()
// {
//     // 1. inversion
//     // 2. conjuction
//     // 3. disjunction
//     // 4. implication
//     // 5. equivalence
// }

int main(int argc, char *argv[])
{

    wstring input = L"(w ∧ z) ∨ ¬y ∨ (¬x ≡ ¬w)";    
    PRINT(parse(input));
    return 0;
}


// // If ... then ...
// void implication(int a, int b)
// {
//     int first[]  { 0, 0, 1, 1 };
//     int second[] { 0, 1, 0, 1 }; 
//     int result[] { 1, 1, 0, 1 };
// }

// // Then and only then
// void equivalence(int a, int b)
// {
//     int first[]  { 0, 0, 1, 1 };
//     int second[] { 0, 1, 0, 1 };
//     int result[] { 1, 0, 0, 1 };
// }
