extern "C"
{

#include "def.h"

istream cin;

istream::istream()
{

}

void istream::pause()
{
	unsigned int key;
	GetKey(&key);
}

void istream::clear()
{
	CLR(this->buffer, 0);
}

// Read a float number
istream & istream::operator >> ( double & val )
{
	this->clear();
	// No error would occur, won't be able to input 2 decimal points
	bool has_point = false;
	unsigned int key; int i = 0;
	while (1)
	{
		GetKey(&key);
		if ( key >= KEY_CHAR_0 && key <= KEY_CHAR_9 && i < IO_LEN - 1 ) {
			(this->buffer)[i] = key - KEY_CHAR_0 + '0';
			(this->buffer)[++i] = 0;
		} else if ( key == KEY_CHAR_DP && !has_point && i < IO_LEN - 1 ) {
			(this->buffer)[i] = '.';
			(this->buffer)[++i] = 0;
			has_point = true;
		} else if ( key == KEY_CTRL_DEL && i ) {
			if ( (this->buffer)[i - 1] == '.' ) has_point = false;
			(this->buffer)[--i] = 0;
		} else if ( key == KEY_CHAR_PMINUS && !i ) {
			(this->buffer)[i] = '-';
			(this->buffer)[++i] = 0;
		} else if ( key == KEY_CTRL_EXE ) {
			// Clear the bottom row
			area_clear(0, 56, 127, 63, 0);
			break;
		} else {
			continue;
		}
		area_clear(0, 56, 127, 63, 0);
		locate(1, ROWS);
		Print(this->buffer);
		// Bdisp_PutDisp_DD();
	}
	val = 0.;
	sscanf((char *)(this->buffer), "%lf", &val);
	return *this;
}

}
