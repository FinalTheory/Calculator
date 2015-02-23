#include "def.h"

void Test_Function()
{
    // Pay attention to thest init vals
    bool is_first = true;
    unsigned int key = KEY_CTRL_EXE;
    while ( true ) {
        if ( !is_first ) GetKey(&key);
        else is_first = false;
        if ( key == KEY_CTRL_EXIT ) {
            return;
        } else if ( key == KEY_CTRL_EXE ) {
            cout.clear();
            cout << "Please input your function:" << endl;
            cout << "f(x) = " << endl;
            Function f;
            cin >> f;
            cout << setprecision(6) << f(1.5) << endl;
        } else {
            continue;
        }
    }
}
