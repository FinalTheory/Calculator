#include "istream.h"
#include "ostream.h"
#include "function.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <math.h>
#include <string.h>

#ifdef __cplusplus
}
#endif // __cplusplus

const int MAX = 12;
double DP[MAX][MAX];

int _pow( int x, int n )
{
	int res = 1;
	for ( int i = 0; i < n; ++i )
		res *= x;
	return res;
}

double calc( Function & f, double a, double b, double prev, int k )
{
	int n = _pow(2, k - 1);
	double tmp = n * 2.;
	double res = 0.;
	for ( int i = 1; i <= n; ++i )
		res += f(a + (2 * i - 1) * (b - a) / tmp);
	res *= ( b - a ) / tmp;
	res += prev / 2.;
	return res;
}

double worker( Function & f, double a, double b )
{
	int m, k, i;
	double tmp;
	CLR(DP, 0);
	i = 1;
	DP[0][0] = ( f(a) + f(b) ) * ( b - a ) / 2.;
	while ( i < MAX ) {
		k = i; m = 0;
		DP[0][i] = calc( f, a, b, DP[0][i - 1], k );
		while ( k > 0 )
		{
			k--; m++;
			tmp = _pow(4, m);
			DP[m][k] = ( DP[m - 1][k + 1] * tmp - DP[m - 1][k] ) / ( tmp - 1 );
		}
		if ( fabs(DP[i][0] - DP[i - 1][0]) < 1e-6 ) break;
		i++;
	}
	// Ensure memory access is safe
	if ( i >= MAX ) i = MAX - 1;
	cout << setprecision(6);
	for ( int x = 0, t = i; x <= i; x++, t-- ) {
        for ( int y = 0; y <= t; y++ ) cout << DP[x][y] << space;
        cout << endl;
	}
	return DP[i][0];
}

void Romberg()
{
    double a, b, res;
    Function f;
    while ( true ) {
        cout.clear();
        cout << "Please input your function to integrate:" << endl;
        cout << "f(x) = " << endl;
        cin >> f;
        f(0.);
        if ( !f.error() ) break;
        else {
            cout.clear();
            cout << "Syntax Error!" << endl;
            cout << "Please input again!" << endl;
            cin.pause();
        }
    }
    cout.clear();
    cout << "Lower bound:" << endl;
    cin >> a;
    cout.clear();
    cout << "Upper bound:" << endl;
    cin >> b;
    cout.clear();
    if ( a > b ) swap(a, b);
    res = worker(f, a, b);
    cout << setprecision(8) << "Final result: " << res << endl;
    cout.display();
}
