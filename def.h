/*
Basic IO Usage

------------------------------------------------
1. cin

1) Supports int and double data type; inputed numbers are showed in the bottom row.
2) If you want to pause the process, just use "cin.pause()", it will get a key and then return.


*/

extern "C"
{
#ifndef DEF_H
#define DEF_H
// Depends on the calculator screen
#define ROWS 8
#define COLS 21
#define MAX_ROWS 64

#define IO_LEN 64
#define MAX_LEN MAX_ROWS * COLS + 1

#define PI 3.14159265
#define CLR(arr,val) memset(arr,val,sizeof(arr))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fxlib.h"

struct Fraction
{
	int up, down;
	Fraction(int _up = 1, int _down = 1);
	void Reduction();
};


// Generate Fraction from double
Fraction getFraction( double val );
// Basic calculations
Fraction operator +( struct Fraction a, struct Fraction b );
Fraction operator -( struct Fraction a, struct Fraction b );
Fraction operator *( struct Fraction a, struct Fraction b );
Fraction operator /( struct Fraction a, struct Fraction b );


struct setprecision
{
	int prec;
	setprecision( int _prec )
	{
		this->prec = _prec;
	}
};

class istream
{
public:
	istream();
	void clear();
	void pause();
	istream & operator >> ( double & val );

	unsigned char buffer[IO_LEN];
};

class ostream
{
public:
	ostream();
	void clear();
	void flush( unsigned char * p_print );
	void display();
	ostream & operator << ( int val );
	ostream & operator << ( double val );
	ostream & operator << ( Fraction val );
	ostream & operator << ( setprecision P );
	ostream & operator << ( char * str );
	ostream & operator << ( ostream & (*pf)(ostream &) );

	int precision;
	unsigned char temp[IO_LEN];
	unsigned char buffer[MAX_LEN];
	// Current write position
	unsigned char * p_write;
	// Current page position
	unsigned char * p_page;
	// End Position
	unsigned char * p_end;
};

// End line & white space
ostream & endl( ostream & os );
ostream & space( ostream & os );


// Clear selected area
void area_clear (int left,int top,int right,int bottom,int sel);

// Pop out a select menu
int pop_menu (char *context[],char *title,int max,int x,int y);

extern ostream cout;
extern istream cin;

/*********************************************************/

void Jacobi();
void Gauss_Seidel();
void LU_solve();
void Gaussian_elimination();

/*********************************************************/

#endif // DEF_H

}
