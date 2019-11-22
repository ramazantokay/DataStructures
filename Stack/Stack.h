//
// Created by altair on 12.11.2019.
//

#ifndef STACKIMP_STACK_H
#define STACKIMP_STACK_H

#include "StackException.h"
#include <iostream>
const int MAX_STACK = 100;

template <class T>
class Stack {
public:
    Stack();                       
    bool isEmpty() const;	    
    void push(const T& newItem);    
    T pop();		            
    T peek() const;                 
    int size();

private:
    T items[MAX_STACK];  	        
    int top;         		       
};

template <class T>
Stack<T>::Stack() { 

    top = -1;
}

template <class T>
bool Stack<T>::isEmpty() const { 
    return top < 0;
}

template <class T>
void Stack<T>::push(const T& newItem) { 

    if (top >= MAX_STACK-1)
        throw StackException("StackException: stack full on push");
    else
        items[++top] = newItem;
}

template <class T>
T Stack<T>::pop() { 

    if (isEmpty())
        throw StackException("StackException: stack empty on pop");
    else 
        return (items[top--]);
}

template <class T>
T Stack<T>::peek() const { 

    if (isEmpty())
        throw StackException("StackException: stack empty on getTop");
    else
        return (items[top]);
}
template <class T>
int Stack<T>::size()
{
    return top;
}

#endif //STACKIMP_STACK_H
