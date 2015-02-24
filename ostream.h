#ifndef OSTREAM_H_INCLUDED
#define OSTREAM_H_INCLUDED

#include "utils.h"

class Fraction;

class setprecision
{
public:
	int prec;
	setprecision( int _prec )
	{
		this->prec = _prec;
	}
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

#endif // OSTREAM_H_INCLUDED
