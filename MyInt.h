//
// Created by ise on 13/01/18.
//

#ifndef ASSIN4_MYINT_H
#define ASSIN4_MYINT_H
#include <iostream>
#include "Variable.h"

using namespace std;


/* MyInt a a kind of Variable.
 *  It has m_value and operators that are virtual (MyInt has own operators).
 */
class MyInt : public Variable
{
private:
    int m_value;

public:
    MyInt();
    MyInt(int value, string name);
    MyInt(string value, string name);
    virtual ~MyInt();

    int getValue()const;
    MyInt operator+ (const Variable& other) const;
    MyInt& operator+= (const Variable& other);
    virtual Variable& operator= (const Variable& other);
    virtual bool operator== (const Variable& other) const;
    virtual void print();
};

#endif //ASSIN4_MYINT_H
