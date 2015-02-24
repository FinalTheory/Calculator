#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif // __cplusplus

template <typename Any>
class Array_1D
{
public:
    Array_1D( int _num ) {
        this->mem_error = false;
        this->num = _num;
        this->p_data = (Any *)malloc(sizeof(Any) * _num);
        if ( this->p_data == NULL ) {
            this->mem_error = true;
        }
        this->clear();
    }
    ~Array_1D() {
        if ( !this->mem_error ) {
            free(this->p_data);
        }
    }
    Any & operator []( int idx ) {
        return this->p_data[idx];
    }
    Array_1D & operator = ( Array_1D & other ) {
        memcpy(this->p_data, other.p_data, sizeof(Any) * this->num);
        return *this;
    }
    bool error() {
        return this->mem_error;
    }
    void clear() {
        if ( !this->mem_error ) {
            memset(this->p_data, 0, sizeof(Any) * this->num);
        }
    }
private:
    bool mem_error;
    int num;
    Any * p_data;
};

template <typename Any>
class Array_2D
{
public:
    Array_2D( int _rows, int _cols ) {
        this->mem_error = false;
        this->rows = _rows;
        this->cols = _cols;
        this->p_data = (Any **)malloc(sizeof(Any *) * _rows);
        if ( this->p_data != NULL ) {
            for ( int i = 0; i < _rows; i++ ) {
                this->p_data[i] = (Any *)malloc(sizeof(Any) * _cols);
                if ( this->p_data[i] == NULL ) {
                    this->mem_error = true;
                    return;
                }
            }
        } else {
            this->mem_error = true;
            return;
        }
        this->clear();
    }
    ~Array_2D() {
        if ( !this->mem_error ) {
            for ( int i = 0; i < this->rows; i++ )
                free(this->p_data[i]);
            free(this->p_data);
        }
    }
    Any * operator []( int row_idx ) {
        return this->p_data[row_idx];
    }
    void clear() {
        if ( !this->mem_error ) {
            for ( int i = 0; i < rows; i++ )
                memset(this->p_data[i], 0, sizeof(Any) * this->cols);
        }
    }
    bool error() {
        return this->mem_error;
    }
private:
    bool mem_error;
    int rows, cols;
    Any ** p_data;
};

#endif // ARRAY_H_INCLUDED
