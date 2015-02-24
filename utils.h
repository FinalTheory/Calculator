#ifndef UTILS_H_
#define UTILS_H_

/*
Basic IO Usage

------------------------------------------------
1. cin

1) Supports int and double data type; inputed numbers are showed in the bottom row.
2) If you want to pause the process, just use "cin.pause()", it will get a key and then return.


*/

// Depends on the calculator screen size
#define ROWS 8
#define COLS 21
#define MAX_ROWS 64
#define MAX_LEN MAX_ROWS * COLS + 1

#define IO_LEN 128

#define MAX_MAT 8

#define PI 3.14159265
#define CLR(arr,val) memset(arr,val,sizeof(arr))

// max,min function
template <typename Any>
Any max( const Any & a, const Any & b ) {
    if ( a >= b ) return a;
    else return b;
}

template <typename Any>
Any min( const Any & a, const Any & b ) {
    if ( a <= b ) return a;
    else return b;
}

// Swap function
template <typename Any>
void swap(Any & a, Any & b) {
    Any tmp;
    tmp = a;
    a = b;
    b = tmp;
}

// Clear selected area
void area_clear (int left,int top,int right,int bottom,int sel);

// Pop out a select menu
int pop_menu (char *context[],char *title,int max,int x,int y);

class istream;
class ostream;

extern ostream cout;
extern istream cin;

#endif // UTILS_H_
