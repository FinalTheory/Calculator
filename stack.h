#ifndef STACK_H_
#define STACK_H_

#define STK_SIZE 64

template <typename Any>
class stack
{
public:
    stack() {this->clear();};
    void clear() {this->pointer = -1;};
    void push(Any val) {this->buf[++this->pointer] = val;};
    void pop() {this->pointer--;};
    Any top() {return this->buf[this->pointer];};
    int size() {return this->pointer + 1;};
private:
    int pointer;
    Any buf[STK_SIZE];
};

#endif
