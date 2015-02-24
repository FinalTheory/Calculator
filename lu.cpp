#include "fraction.h"
#include "istream.h"
#include "ostream.h"

static Fraction A[8][8], b[8];

int LU_input()
{
	double tmp;
	cout.clear();
	cout << "Please input demension of the matrix:" << endl;
	cin >> tmp;
	int n = int(tmp);
	for ( int i = 1; i <= n; ++i )
		for ( int j = 1; j <= n; ++j )
		{
			cout.clear();
			cout << "Input A(" << i << ", " << j << "):" << endl;
			cin >> tmp;
			A[i][j] = getFraction(tmp);
		}
	for ( int i = 1; i <= n; ++i )
	{
		cout.clear();
		cout << "Input b(" << i << "):" << endl;
		cin >> tmp;
		b[i] = getFraction(tmp);
	}
	return n;
}

void LU_output( int n )
{
	cout.clear();
	cout << "LU = " << endl;
	for ( int i = 1; i <= n; ++i )
	{
		for ( int j = 1; j <= n; ++j )
			cout << A[i][j] << space;
		cout << endl;
	}
	cout << "x = " << endl;
	for ( int i = 1; i <= n; ++i )
		cout << b[i] << endl;
	cout.display();
}

void LU_solve()
{
	int n = LU_input();
	// LU factorization
	Fraction sum;
	for ( int k = 1; k <= n; ++k )
	{
		// calculate u
		for ( int j = k; j <= n; ++j )
		{
			sum = getFraction(0);
			for ( int i = 1; i <= k - 1; ++i )
				sum = sum + A[k][i] * A[i][j];
			A[k][j] = A[k][j] - sum;
		}
		// calculate l
		for ( int i = k + 1; i <= n; ++i )
		{
			sum = getFraction(0);
			for ( int j = 1; j <= k - 1; ++j )
				sum = sum + A[i][j] * A[j][k];
			A[i][k] = ( A[i][k] - sum ) / A[k][k];
		}
	}
	// solve Ly = b
	for ( int k = 2; k <= n; ++k )
	{
		sum = 0.;
		for ( int j = 1; j <= k - 1; ++j )
			sum = sum + A[k][j] * b[j];
		b[k] = b[k] - sum;
	}
	// solve Ux = y
	b[n] = b[n] / A[n][n];
	for ( int k = n - 1; k >= 1; --k )
	{
		sum = 0.;
		for ( int j = k + 1; j <= n; ++j )
			sum = sum + A[k][j] * b[j];
		b[k] = ( b[k] - sum ) / A[k][k];
	}
	LU_output(n);
}
