#include "def.h"

ostream cout;

ostream & endl( ostream & os )
{
	while ( ( os.p_write - os.buffer ) % COLS && os.p_write < os.p_end ) os.p_write++;
	os.flush(os.p_page);
	return os;
}

ostream & space( ostream & os )
{
	if ( os.p_write < os.p_end ) *(os.p_write++) = ' ';
	return os;
}

ostream::ostream()
{
	this->clear();
}

void ostream::clear()
{
	Bdisp_AllClr_DDVRAM();
	this->precision = 3;
	this->p_write = this->buffer;
	this->p_page = this->buffer;
	this->p_end = this->buffer + MAX_LEN;
	CLR(this->buffer, 0);
}

void ostream::flush( unsigned char * p_print )
{
	// Clear screen area
	Bdisp_AllClr_DDVRAM();
	for ( int i = 0; i < ROWS; ++i )
	{
		locate(1, i + 1);
		for ( int j = 0; j < COLS; ++j )
			PrintC(p_print + i * COLS + j);
	}
	Bdisp_PutDisp_DD();
}

void ostream::display()
{
	unsigned int key;
	unsigned char * p_print = this->p_page;
	// Display the first several rows
	this->flush(p_print);
	// Then switch to the other rows
	while (1)
	{
		GetKey(&key);
		if ( key == KEY_CTRL_UP && p_print != buffer ){
			p_print -= ROWS * COLS;
			this->flush(p_print);
		} else if ( key == KEY_CTRL_DOWN && p_print != p_end - ROWS * COLS - 1 ) {
			p_print += ROWS * COLS;
			this->flush(p_print);
		} else if ( key == KEY_CTRL_EXIT || key == KEY_CTRL_EXE ) {
			return;
		}
	}
}

ostream & ostream::operator << ( int val )
{
    sprintf((char *)(this->temp), "%d", val);
    int len = strlen((char *)(this->temp));
    // Write into video buffer if not exceed limit
    // And then update page pointer
    if ( this->p_write + len < this->p_end ) {
    	strcpy((char *)(this->p_write), (char *)(this->temp));
    	this->p_write += len;
    	this->p_page = this->p_write - ( this->p_write - this->buffer ) % ( ROWS * COLS );
    }
    return *this;
}

ostream & ostream::operator << ( double val )
{
	char fmt[16];
	sprintf(fmt, "%%.%dlf", this->precision);
    sprintf((char *)(this->temp), fmt, val);
    int len = strlen((char *)(this->temp));
    // Write into video buffer if not exceed limit
    // And then update page pointer
    if ( this->p_write + len < this->p_end ) {
    	strcpy((char *)(this->p_write), (char *)(this->temp));
    	this->p_write += len;
    	this->p_page = this->p_write - ( this->p_write - this->buffer ) % ( ROWS * COLS );
    }
    return *this;
}

ostream & ostream::operator << ( Fraction val )
{
	if ( val.down != 1 )
    	sprintf((char *)(this->temp), "%d/%d", val.up, val.down);
    else
    	sprintf((char *)(this->temp), "%d", val.up);
    int len = strlen((char *)(this->temp));
    // Write into video buffer if not exceed limit
    // And then update page pointer
    if ( this->p_write + len < this->p_end ) {
    	strcpy((char *)(this->p_write), (char *)(this->temp));
    	this->p_write += len;
    	this->p_page = this->p_write - ( this->p_write - this->buffer ) % ( ROWS * COLS );
    }
    return *this;
}

ostream & ostream::operator << ( char * str )
{
    int len = strlen(str);
    // Write into video buffer if not exceed limit
    // And then update page pointer
    if ( this->p_write + len < this->p_end ) {
    	strcpy((char *)(this->p_write), str);
    	this->p_write += len;
    	this->p_page = this->p_write - ( this->p_write - this->buffer ) % ( ROWS * COLS );
    }
    return *this;
}

ostream & ostream::operator << ( ostream & (*pf)(ostream &) )
{
	return pf(*this);
}

ostream & ostream::operator << ( setprecision P )
{
	this->precision = P.prec;
	return *this;
}

void area_clear (int left,int top,int right,int bottom,int sel)
{
    DISPBOX box;
    box.left = left; box.top = top; box.right = right; box.bottom = bottom;
    if (sel != 1) Bdisp_AreaClr_DDVRAM (&box);
    if (sel != 0) {
		Bdisp_DrawLineVRAM (box.left,box.top,box.right,box.top);
		Bdisp_DrawLineVRAM (box.left,box.bottom,box.right,box.bottom);
		Bdisp_DrawLineVRAM (box.left,box.top,box.left,box.bottom);
		Bdisp_DrawLineVRAM (box.right,box.top,box.right,box.bottom);
    }
}

int pop_menu (char *context[],char *title,int max,int x,int y)
{
    int width, height, i, l, redraw = 1, index = 0;
    unsigned int key;
    height = ( max + 1 ) * 8;
    width = strlen(title);
    for ( i = 0; i < max; ++i ) {
        l = strlen(context[i]);
        if ( l > width ) width = l;
    }
    width *= 6;
    area_clear(x,y,x+width+2,y+height+1,2);
    PrintXY (x+1,y+1,(unsigned char*)title,0);
    Bdisp_AreaReverseVRAM (x+1,y+1,x+width+1,y+8);
    while (1){
        if (redraw) {
            redraw = 0;
            area_clear(x+1,y+9,x+width+1,y+height,0);
            for (i=0;i<max;++i)
            PrintXY(x+1,y+1+(i+1)*8,(unsigned char *)context[i],0);
            Bdisp_AreaReverseVRAM(x+1,y+1+(index+1)*8,x+width+1,y+(index+2)*8);
        }
        GetKey(&key);
        if (key==KEY_CTRL_UP){
            index--;
            if (index<0) index = max-1;
            redraw = 1;
        }
        else if (key==KEY_CTRL_DOWN){
           index++;
           if (index>=max) index = 0;
            redraw = 1;
        }
        else if (key==KEY_CTRL_EXIT) return -1;
        else if (key==KEY_CTRL_EXE) return index;
    }
}
