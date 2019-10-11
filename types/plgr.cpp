#include "string.h"
using namespace std;


int main()
{
    dtf::string name {"Artyom"}, surname {"Danilov"}, thirdname {"Igorevich"};
    dtf::string full_name = name + " " + surname + " " + thirdname;
    full_name += " is a software developer.";
    cout << full_name << endl;
}