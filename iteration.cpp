#include "istream.h"
#include "ostream.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <string.h>

#ifdef __cplusplus
}
#endif // __cplusplus

static double A[8][8], b[8], x[8], x_prev[8];

void iter_input( int & n, int & max_steps )
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

void iter_output( int n, int step )
{
	cout << "Step NO." << step << ":" << endl;
	for ( int i = 1; i <= n; ++i ) cout << x[i] << space;
	cout << endl;
}

void Jacobi()
{
	double sum;
	int n, max_steps;
	iter_input(n, max_steps);
	cout.clear();
	cout << setprecision(4);
	for ( int i = 1; i <= n; ++i ) x_prev[i] = x[i] = 0.;
	iter_output(n, 0);
	for ( int k = 1; k <= max_steps; ++k )
	{
		for ( int i = 1; i <= n; ++i )
		{
			sum = 0.;
			for ( int j = 1; j <= n; ++j ) if ( j != i )
				sum += A[i][j] * x_prev[j];
			x[i] = ( b[i] - sum ) / A[i][i];
		}
		iter_output(n, k);
		memcpy( x_prev, x, sizeof(x_prev) );
	}
	cout.display();
}


void Gauss_Seidel()
{
	double sum1, sum2;
	int n, max_steps;
	iter_input(n, max_steps);
	cout.clear();
	cout << setprecision(4);
	for ( int i = 1; i <= n; ++i ) x_prev[i] = x[i] = 0.;
	iter_output(n, 0);
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
		iter_output(n, k);
		memcpy( x_prev, x, sizeof(x_prev) );
	}
	cout.display();
}
