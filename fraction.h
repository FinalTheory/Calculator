#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

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

#endif // FRACTION_H_INCLUDED
