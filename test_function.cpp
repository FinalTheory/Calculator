#include "def.h"

void TestFunction()
{
    cout.clear();
    cout << "Please input your function" << endl;
    Function f;
    cin >> f;
    cout << setprecision(6) << f(1.5) << endl;
}
