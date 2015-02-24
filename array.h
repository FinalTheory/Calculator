#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <string.h>

#ifdef __cplusplus
}
#endif // __cplusplus

template <typename Any>
class Array_1D
{
public:
    Array_1D( int num ) {
        this->num = num;
        this->p_data = new Any[num];
    }
    ~Array_1D() {
        delete this->p_data;
    }
    Any & operator []( int idx ) {
        return this->p_data[idx];
    }
    Array_1D & operator = ( Array_1D & other ) {
        memcpy(this->p_data, other.p_data, sizeof(Any) * num);
        return *this;
    }
private:
    int num;
    Any * p_data;
};

template <typename Any>
class Array_2D
{
public:
    Array_2D( int rows, int cols ) {
        this->rows = rows;
        this->cols = cols;
        this->p_data = new Any*[rows];
        for ( int i = 0; i < rows; i++ )
            this->p_data[i] = new Any[cols];
    }
    ~Array_2D() {
        for ( int i = 0; i < this->rows; i++ )
            delete this->p_data[i];
        delete this->p_data;
    }
    Any * operator []( int row_idx ) {
        return this->p_data[row_idx];
    }
    void clear() {
        for ( int i = 0; i < rows; i++ )
            memset(this->p_data[i], 0, sizeof(Any) * this->cols);
    }
private:
    int rows, cols;
    Any ** p_data;
};

#endif // ARRAY_H_INCLUDED
