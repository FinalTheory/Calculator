#ifndef ISTREAM_H_INCLUDED
#define ISTREAM_H_INCLUDED

#include "utils.h"

// Forward declaration
class Function;

class istream
{
public:
	istream();
	void clear();
	void pause();
	istream & operator >> ( double & );
	istream & operator >> ( Function & );

private:
	unsigned char buffer[IO_LEN];
	unsigned char * get_key_name( unsigned int );
	// Flush all the data in buffer to screen
	void flush_buffer();
};

#endif // ISTREAM_H_INCLUDED
