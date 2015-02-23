#include "def.h"

istream cin;

istream::istream() {

}

unsigned char * istream::get_key_name( unsigned int key ) {
    switch ( key ) {
        case KEY_CHAR_PLUS:
            return "+";
        case KEY_CHAR_MINUS:
            return "-";
        case KEY_CHAR_MULT:
            return "*";
        case KEY_CHAR_DIV:
            return "/";
        case KEY_CHAR_POW:
            return "^";
        case KEY_CHAR_LPAR:
            return "(";
        case KEY_CHAR_RPAR:
            return ")";
        case KEY_CHAR_SIN:
            return "sin(";
        case KEY_CHAR_COS:
            return "cos(";
        case KEY_CHAR_TAN:
            return "tan(";
        case KEY_CHAR_LOG:
            return "log(";
        case KEY_CHAR_LN:
            return "ln(";
        case KEY_CHAR_EXP:
            return "exp(";
        case KEY_CHAR_ROOT:
            return "sqrt(";
        case KEY_CHAR_PMINUS:
            return "(-)";
        case KEY_CHAR_DP:
            return ".";
        case KEY_CHAR_0:
            return "0";
        case KEY_CHAR_1:
            return "1";
        case KEY_CHAR_2:
            return "2";
        case KEY_CHAR_3:
            return "3";
        case KEY_CHAR_4:
            return "4";
        case KEY_CHAR_5:
            return "5";
        case KEY_CHAR_6:
            return "6";
        case KEY_CHAR_7:
            return "7";
        case KEY_CHAR_8:
            return "8";
        case KEY_CHAR_9:
            return "9";
            //User shouldn't input comma to create a function
//        case KEY_CHAR_COMMA:
//            return ",";
        case KEY_CHAR_X:
            return "x";
    }
    return NULL;
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
istream & istream::operator >> ( double & val ) {
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
		this->flush_buffer();
	}
	val = 0.;
	sscanf((char *)(this->buffer), "%lf", &val);
	return *this;
}

void istream::flush_buffer() {
    unsigned char ch, *p = this->buffer;
    int buf_length = strlen((char *)this->buffer);
    int rows = buf_length / COLS + ( buf_length % COLS ? 1 : 0 );
    // If nothing in the buffer, just clear the bottom row
    if ( rows == 0 ) {
        area_clear(0, 56, 127, 63, 0);
        return;
    }
    int start_row = ROWS - rows + 1;
    //First clear the corresponding area
    area_clear(0, (ROWS - rows) * 8, 127, 63, 0);
    for ( int cur_row = start_row; cur_row <= ROWS; cur_row++, p += COLS ) {
        // Set a null here to terminate the first line
        ch = *( p + COLS );
        *( p + COLS ) = 0;
        // Then print current line
        locate(1, cur_row);
        Print(p);
        // Finally write that char back
        *( p + COLS ) = ch;
    }
}

istream & istream::operator >> ( Function & f ) {
    this->clear();
    unsigned int key;
    unsigned char * key_name;
    // Record function contents
    unsigned char func[FUNC_LEN];
    int p_func = 0;

    while ( true ) {
        GetKey(&key);
        // First check if it is a char of function body
        if ( ( key_name = this->get_key_name(key) ) != NULL ) {
            func[p_func++] = key;
            strcat((char *)this->buffer, (char *)key_name);
        } else if ( key == KEY_CTRL_DEL ) {
            if ( p_func > 0 )  {
                p_func--;
                int total_len = strlen((char *)this->buffer);
                int len = strlen((char *)get_key_name(func[p_func]));
                this->buffer[total_len - len] = 0;
            }
        } else if ( key == KEY_CTRL_EXE ) {
            func[p_func] = 0;
            f.set_func(func);
            break;
        } else {
            continue;
        }
        this->flush_buffer();
    }
    return *this;
}
