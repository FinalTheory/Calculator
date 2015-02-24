#include "fraction.h"
#include "istream.h"
#include "ostream.h"
#include "array.h"

int Gauss_input( Array_2D<Fraction> & A, Array_1D<Fraction> & b )
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

void Gauss_output( int n, Array_2D<Fraction> & A, Array_1D<Fraction> & b )
{
	cout << "A = " << endl;
	for ( int i = 1; i <= n; ++i )
	{
		for ( int j = 1; j <= n; ++j )
			cout << A[i][j] << space;
		cout << endl;
	}
	cout << "b = " << endl;
	for ( int i = 1; i <= n; ++i )
		cout << b[i] << endl;
}


void Gaussian_elimination()
{
    Array_2D<Fraction> A(MAX_MAT, MAX_MAT);
    Array_1D<Fraction> b(MAX_MAT);
	int n = Gauss_input(A, b);
	cout.clear();
	for ( int k = 1; k <= n - 1; ++k )
	{
		// elimination
		for ( int i = k + 1; i <= n; ++i )
		{
			Fraction m = A[i][k] / A[k][k];
			for ( int j = k; j <= n; ++j )
				A[i][j] = A[i][j] - A[k][j] * m;
			b[i] = b[i] - b[k] * m;
		}
		cout << "Step NO." << k << ":" << endl;
		Gauss_output(n, A, b);
	}
	// back substitution
	for ( int i = n; i >= 1; --i )
	{
		Fraction sum = getFraction(0);
		for ( int j = i + 1; j <= n; ++j )
			sum = sum + A[i][j] * b[j];
		b[i] = ( b[i] - sum ) / A[i][i];
	}
	cout << "Final result:" << endl;
	cout << "b = " << endl;
	for ( int i = 1; i <= n; ++i )
		cout << b[i] << endl;
	cout.display();
}
