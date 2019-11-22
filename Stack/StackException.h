//
// Created by altair on 12.11.2019.
//

#ifndef STACKIMP_STACKEXCEPTION_H
#define STACKIMP_STACKEXCEPTION_H

#include <string>
using namespace std;

class StackException
{
public:
    StackException(string err){
        error = err;}
        string error;
};
#endif //STACKIMP_STACKEXCEPTION_H
