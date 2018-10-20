//
// Created by ise on 18/01/18.
//

#ifndef ASSIN4_VARIABLENOTFOUNDEXCEPTION_H
#define ASSIN4_VARIABLENOTFOUNDEXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;
class VariableNotFoundException : public exception
{
public:
    virtual const char* what() const throw(){
        return "VariableNotFoundException";
    }
};

#endif //ASSIN4_VARIABLENOTFOUNDEXCEPTION_H
