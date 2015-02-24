#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#define FUNC_LEN 128

class Function
{
public:
    Function() {this->func_expr[0] = 0; this->func_error = false;};
    double operator() ( double );
    void set_func( unsigned char * );
    bool error() {return this->func_error; };

private:
    unsigned char *read_number( unsigned char *, double & );
    int get_oper_idx(unsigned char);
    double calc_binary(double, unsigned char, double);
    double calc_unary(double, unsigned char);

    bool func_error;
    unsigned char func_expr[FUNC_LEN];
    const static int Priority[15][15];
};

#endif // FUNCTION_H_INCLUDED
