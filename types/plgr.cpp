#include "string.h"
using namespace std;


int main()
{
    dtf::string name {"Artyom"}, surname {"Danilov"}, thirdname {"Igorevich"};
    cout << name[0] << " " << name[name.length() - 1] << endl;
    cout << name[name.length()];
}