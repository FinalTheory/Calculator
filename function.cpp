#include "function.h"
#include "stack.h"

#ifndef TEST

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fxlib.h>

#ifdef __cplusplus
}
#endif // __cplusplus

#else // TEST

#include "keybios.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
void output_names( unsigned char * );

#endif // TEST

const int Function :: Priority[15][15] = {
    { 1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1 },
    { 1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1 },
    { 1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1 },
    { 1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1 },
    { 1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-2 },
    { -1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,0 },
};

void str2num( unsigned char *str ) {
    for ( unsigned i = 0; i < strlen((char *)str); i++ ) {
        if ( str[i] == '-' ) str[i] = KEY_CHAR_PMINUS;
        else if ( str[i] == '.' ) str[i] = KEY_CHAR_DP;
        else if ( '0' <= str[i] && str[i] <= '9' ) str[i] = str[i] - '0' + KEY_CHAR_0;
    }
}

bool is_digit( unsigned char ch ) {
    if ( (KEY_CHAR_0 <= ch && ch <= KEY_CHAR_9) \
        || ch == KEY_CHAR_DP \
        || ch == KEY_CHAR_PMINUS ) return true;
    return false;
}

void Function :: set_func( unsigned char * buf ) {
    this->func_error = false;
    strcpy((char *)this->func_expr, (char *)buf);
}

int Function :: get_oper_idx( unsigned char oper ) {
    switch ( oper ) {
        case KEY_CHAR_PLUS:
            return 0;
        case KEY_CHAR_MINUS:
            return 1;
        case KEY_CHAR_MULT:
            return 2;
        case KEY_CHAR_DIV:
            return 3;
        case KEY_CHAR_POW:
            return 4;
        case KEY_CHAR_LPAR:
            return 5;
        case KEY_CHAR_RPAR:
            return 6;
        case KEY_CHAR_SIN:
            return 7;
        case KEY_CHAR_COS:
            return 8;
        case KEY_CHAR_TAN:
            return 9;
        case KEY_CHAR_LOG:
            return 10;
        case KEY_CHAR_LN:
            return 11;
        case KEY_CHAR_EXP:
            return 12;
        case KEY_CHAR_ROOT:
            return 13;
        case KEY_CHAR_COMMA:
            return 14;
        default:
            return -1;
    }
}

unsigned char * Function :: read_number( unsigned char *p, double & val ) {
    val = 0.;
    // First check if it is negative
    double coeff = 1.;
    if ( *p == KEY_CHAR_PMINUS ) {
        p++;
        coeff = -coeff;
    }
    // Then try to read the integer part
    for ( ; KEY_CHAR_0 <= *p && *p <= KEY_CHAR_9; p++ ) {
        val *= 10.;
        val += ( *p - KEY_CHAR_0 );
    }
    // If we get a decimal point, then continue to read the fractional part
    if ( *p == KEY_CHAR_DP ) {
        p++;
        double digit_base = 0.1;
        for ( ; KEY_CHAR_0 <= *p && *p <= KEY_CHAR_9; p++ ) {
            val += digit_base * ( *p - KEY_CHAR_0 );
            digit_base *= 0.1;
        }
    }
    // Final, multiply the coeffcient and return
    val *= coeff;
    return p;
}

double Function :: calc_binary( double A, unsigned char oper, double B ) {
	switch ( oper )
	{
		case KEY_CHAR_PLUS:
			return A + B;
		case KEY_CHAR_MINUS:
			return A - B;
		case KEY_CHAR_MULT:
			return A * B;
		case KEY_CHAR_DIV:
			return A / B;
		case KEY_CHAR_POW:
			return pow( A, B );
        default:
            this->func_error = true;
            return 0.;
	}
}

double Function :: calc_unary( double x, unsigned char oper ) {
    switch ( oper ) {
        case KEY_CHAR_LPAR:
        case KEY_CHAR_COMMA:
            return x;
        case KEY_CHAR_SIN:
            return sin(x);
        case KEY_CHAR_COS:
            return cos(x);
        case KEY_CHAR_TAN:
            return tan(x);
        case KEY_CHAR_LOG:
            return log10(x);
        case KEY_CHAR_LN:
            return log(x);
        case KEY_CHAR_EXP:
            return exp(x);
        case KEY_CHAR_ROOT:
            return sqrt(x);
        default:
            this->func_error = true;
            return 0.;
    }
}

double Function :: operator()( double x ) {
    this->func_error = false;
    double cur_val, val_a, val_b;
    unsigned char real_expr[FUNC_LEN], oper, comma[2] = {KEY_CHAR_COMMA, 0};

    // First insert the left comma
    strcpy((char *)real_expr, (char *)comma);
    // Then copy the expr
    strcat((char *)real_expr, (char *)this->func_expr);
    // Finally insert the right comma
    strcat((char *)real_expr, (char *)comma);

    // Until here, all the expr sequence should be right
    // Add a test here
    // output_names(real_expr);

    stack<unsigned char> oper_stk;
    stack<double> num_stk;
    // Put first comma into operator stack
    oper_stk.push(real_expr[0]);
    unsigned char *p = real_expr + 1;
    while ( *p ) {
        // If this is a variable, just push the corresponding value
        if ( *p == KEY_CHAR_X ) {
            num_stk.push(x); p++;
        } else if ( is_digit(*p) ) {
            // If this is a digit, then just read the float number
            p = Function::read_number(p, cur_val);
            num_stk.push(cur_val);
        } else {
            if ( oper_stk.size() < 1 ) {
                this->func_error = true;
                return 0.;
            }
            switch( Function::Priority[get_oper_idx(oper_stk.top())][get_oper_idx(*p)] ) {
                case 1:
                    if ( num_stk.size() < 2 ) {
                        this->func_error = true;
                        return 0.;
                    }
                    oper = oper_stk.top(); oper_stk.pop();
                    val_b = num_stk.top(); num_stk.pop();
                    val_a = num_stk.top(); num_stk.pop();
                    num_stk.push(calc_binary(val_a, oper, val_b));
                    break;
                case -1:
                    oper_stk.push(*p);
                    p++;
                    break;
                case 0:
                    if ( num_stk.size() < 1 ) {
                        this->func_error = true;
                        return 0.;
                    }
                    // Note that binary operations act like brackets
                    // Example: sin(), cos(), exp() and so on
                    oper = oper_stk.top(); oper_stk.pop();
                    cur_val = num_stk.top(); num_stk.pop();
                    num_stk.push(calc_unary(cur_val, oper));
                    p++;
                    break;
                default:
                    this->func_error = true;
                    return 0.;
            }
        }
    }
    if ( num_stk.size() != 1 || oper_stk.size() != 0 ) {
        this->func_error = true;
        return 0.;
    }
    return num_stk.top();
}
