//
// Created by ise on 18/01/18.
//

#ifndef ASSIN4_BADVARIABLETYPEEXCEPTION_H
#define ASSIN4_BADVARIABLETYPEEXCEPTION_H
#include <iostream>
#include <exception>

using namespace std;
class BadVariableTypeException : public exception
{
public:
    virtual const char* what() const throw(){
            return "BadVariableTypeException";
    }
};

#endif //ASSIN4_BADVARIABLETYPEEXCEPTION_H
