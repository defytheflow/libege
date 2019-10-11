#include "string.h"
using namespace std;


int main()
{
    dtf::string name {"Artyom"};
    cout << name << endl;
    cout << "Length: " << name.length() << endl;
    cout << "Capacity: " << name.capacity() << endl;
}