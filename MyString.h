//
// Created by ise on 13/01/18.
//

#ifndef ASSIN4_MYSTRING_H
#define ASSIN4_MYSTRING_H
#include <iostream>
#include "Variable.h"

/* MyString a a kind of Variable.
 *  It has m_value and operators that are virtual (MyString has own operators).
 */
using namespace std;

class MyString : public Variable
{
private:
    string m_value;

public:
    MyString();
    MyString(string value, string name);
    virtual ~MyString();

    string setValue(string value);
    string getValue()const;
    virtual Variable& operator= (const Variable& other);
    virtual bool operator== (const Variable& other) const;
    virtual void print();
};

#endif //ASSIN4_MYSTRING_H
