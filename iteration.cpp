#include "istream.h"
#include "ostream.h"
#include "array.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <string.h>

#ifdef __cplusplus
}
#endif // __cplusplus

void iter_input( int & n, int & max_steps,
                Array_2D<double> & A, Array_1D<double> & b )
{
	double tmp;
	cout.clear();
	cout << "Please input demension of the matrix:" << endl;
	cin >> tmp;
	n = int(tmp);
	cout << "Please input max steps:" << endl;
	cin >> tmp;
	max_steps = int(tmp);

	for ( int i = 1; i <= n; ++i )
		for ( int j = 1; j <= n; ++j )
		{
			cout.clear();
			cout << "Input A(" << i << ", " << j << "):" << endl;
			cin >> A[i][j];

		}
	for ( int i = 1; i <= n; ++i )
	{
		cout.clear();
		cout << "Input b(" << i << "):" << endl;
		cin >> b[i];
	}
}

void iter_output( int n, int step, Array_1D<double> & x )
{
	cout << "Step NO." << step << ":" << endl;
	for ( int i = 1; i <= n; ++i ) cout << x[i] << space;
	cout << endl;
}

void Jacobi()
{
    Array_1D<double> b(MAX_MAT), x_prev(MAX_MAT), x(MAX_MAT);
    Array_2D<double> A(MAX_MAT, MAX_MAT);
	double sum;
	int n, max_steps;
	iter_input(n, max_steps, A, b);
	cout.clear();
	cout << setprecision(4);
	for ( int i = 1; i <= n; ++i ) x_prev[i] = x[i] = 0.;
	iter_output(n, 0, x);
	for ( int k = 1; k <= max_steps; ++k )
	{
		for ( int i = 1; i <= n; ++i )
		{
			sum = 0.;
			for ( int j = 1; j <= n; ++j ) if ( j != i )
				sum += A[i][j] * x_prev[j];
			x[i] = ( b[i] - sum ) / A[i][i];
		}
		iter_output(n, k, x);
		x_prev = x;
	}
	cout.display();
}


void Gauss_Seidel()
{
    Array_1D<double> b(MAX_MAT), x_prev(MAX_MAT), x(MAX_MAT);
    Array_2D<double> A(MAX_MAT, MAX_MAT);
	double sum1, sum2;
	int n, max_steps;
	iter_input(n, max_steps, A, b);
	cout.clear();
	cout << setprecision(4);
	for ( int i = 1; i <= n; ++i ) x_prev[i] = x[i] = 0.;
	iter_output(n, 0, x);
	for ( int k = 1; k <= max_steps; ++k )
	{
		sum1 = 0.;
		for ( int j = 2; j <= n; ++j ) sum1 += A[1][j] * x_prev[j];
		x[1] = ( b[1] - sum1 ) / A[1][1];
		for ( int i = 2; i <= n - 1; ++i )
		{
			sum1 = sum2 = 0.;
			for ( int j = 1; j <= i - 1; ++j ) sum1 += A[i][j] * x[j];
			for ( int j = i + 1; j <= n; ++j ) sum2 += A[i][j] * x_prev[j];
			x[i] = ( b[i] - sum1 - sum2 ) / A[i][i];
		}
		sum1 = 0.;
		for ( int j = 1; j <= n - 1; ++j ) sum1 += A[n][j] * x[j];
		x[n] = ( b[n] - sum1 ) / A[n][n];
		iter_output(n, k, x);
		x_prev = x;
	}
	cout.display();
}
