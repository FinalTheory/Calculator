#include "function.h"
#include "istream.h"
#include "ostream.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <fxlib.h>

#ifdef __cplusplus
}
#endif // __cplusplus

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
            cout << "Please input your function and x:" << endl;
            cout << "f(x) = ?" << endl;
            Function f;
            cin >> f;
            double x, res;
            cout << "x = ?" << endl;
            cin >> x; res = f(x);
            cout.clear();
            if ( f.error() ) cout << "Syntax Error!" << endl;
            else cout << "f(x) = " << setprecision(6) << f(x) << endl;
        } else {
            continue;
        }
    }
}
