//
// Created by ise on 18/01/18.
//

#ifndef ASSIN4_ARRAYOUTOFBOUNDEXCEPTION_H
#define ASSIN4_ARRAYOUTOFBOUNDEXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;
class ArrayOutOfBoundException : public exception
{
public:
    virtual const char* what() const throw(){
        return "ArrayOutOfBoundException";
    }
};
#endif //ASSIN4_ARRAYOUTOFBOUNDEXCEPTION_H
