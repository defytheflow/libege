#include "common.h"
#include "num_conv.h"
using namespace std;

typedef string (*numConvFunc)(string, int); 

void test_error(string func, string test_case, string exp_res, string res)
{
    cerr << "Test failed in function " + func << endl;
    cerr << "Testcase - " + test_case + ", Expected result - " + exp_res +
            ". Result - " + res << endl;
}

void test_success(string func)
{
    cout << func << " - All tests are successful." << endl;
}

void test_func(numConvFunc func, string test_cases[], string exp_test_res[], int num_test_cases, int *numErrors)
{
    for (int i {0}; i < num_test_cases; ++i)
    {
        string res = bin(test_cases[i], DECIMAL);
        if (res != exp_test_res[i])
        {
            ++(*numErrors);
            test_error("bin()", test_cases[i], exp_test_res[i], res);
        }
    }
}

void test_bin()
{
#define NUM_TEST_CASES 7
    int numErrors {0};

    // DECIMAL --> BINARY
    string test_cases1[NUM_TEST_CASES] = {"0", "-2", "34", "21", "185", "1432", "3"};
    // 'exp' stands for 'expected', 'res' for 'results'
    string exp_test_res1[NUM_TEST_CASES] = {"0", "", "100010", "10101", "10111001", "10110011000", "11"};
        
    test_func(bin, test_cases1, exp_test_res1, NUM_TEST_CASES, &numErrors);

    if (numErrors == 0)
        test_success("bin()");

#undef NUM_TEST_CASES
}

int main()
{
    test_bin();
    return 0;
}