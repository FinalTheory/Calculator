#include "fraction.h"
#include "utils.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
}
#endif // __cplusplus

int gcd( int a, int b )
{
	if ( b == 0 ) return a;
	return gcd(b, a % b);
}

Fraction getFraction( double val )
{
	char tmp[16];
	sprintf(tmp, "%lf", val);
	int len = strlen(tmp), pos = -1, up, down;
	for ( int i = 0; i < len; ++i ) if ( tmp[i] == '.' ) {pos = i; break;}
	if ( pos == -1 ) {
		sscanf(tmp, "%d", &up);
		down = 1;
	} else {
		int left, right;
		down = 1;
		for ( int i = 0; i < len - pos - 1; ++i ) down *= 10;
		tmp[pos] = ' ';
		sscanf(tmp, "%d %d", &left, &right);
		up = left * down + right;
	}
	return Fraction(up, down);
}

Fraction::Fraction(int _up, int _down)
{
	this->up = _up;
	this->down = _down;
	this->Reduction();
}

void Fraction::Reduction()
{
	int a = abs(this->up), b = abs(this->down), tmp;
	if ( a < b ) swap(a, b);
	tmp = gcd(a, b);
	this->up /= tmp;
	this->down /= tmp;
	if ( this->up * this->down < 0 )
	{
		this->up = -abs(this->up);
		this->down = abs(this->down);
	}
	else
	{
		this->up = abs(this->up);
		this->down = abs(this->down);
	}
}

Fraction operator +( struct Fraction a, struct Fraction b )
{

	return Fraction(a.up * b.down + b.up * a.down, a.down * b.down);
}

Fraction operator -( struct Fraction a, struct Fraction b )
{
	b.up = -b.up;
	return a + b;
}

Fraction operator *( struct Fraction a, struct Fraction b )
{
	return Fraction(a.up * b.up, a.down * b.down);
}

Fraction operator /( struct Fraction a, struct Fraction b )
{
	swap(b.up, b.down);
	return a * b;
}
