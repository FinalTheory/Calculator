#include "istream.h"
#include "ostream.h"
#include "array.h"

void Newton_Interp() {
    int n;
    cout.clear();
    cout << "Please input number of data points:" << endl;
    cin >> n;
    Array_2D<double> dp(n, n);
    Array_1D<double> x(n), f_x(n);
    if ( dp.error() || x.error() || f_x.error() ) {
        cout.clear();
        cout << "Memory allocation failed!" << endl;
        cout << "Press [EXE] to return." << endl;
        goto finish;
    }
    for ( int i = 0; i < n; i++ ) {
        cout.clear();
        cout << "Input x" << i << ":" << endl;
        cin >> x[i];
        cout << "Input f(x" << i << "):" << endl;
        cin >> f_x[i];
    }
    for ( int i = 0; i < n; i++ ) dp[i][0] = f_x[i];
    for ( int row = 1; row < n; row++ )
        for ( int col = 1; col <= row; col++ )
            dp[row][col] = ( dp[row][col - 1] - dp[row - 1][col - 1] ) / ( x[row] - x[row - col] );
    cout.clear();
    cout << setprecision(3) << "Difference quotient table:" << endl;
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j <= i; j++ ) cout << dp[i][j] << space;
        cout << endl;
    }
finish:
    cout.display();
}
