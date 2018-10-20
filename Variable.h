//
// Created by ise on 13/01/18.
//

#ifndef ASSIN4_VARIABLE_H
#define ASSIN4_VARIABLE_H
#include <iostream>
#include "BadVariableTypeException.h"

using namespace std;

/* Variable is an abstract object- it childs can be MyInt, MyString or MyBool array.
 *  It has name, and operators.
 */
class Variable{
    string m_name;

public:
    Variable(string name):m_name(name){};
    virtual ~Variable();

    bool currentVar (string name);
    virtual string getName()const;
    virtual Variable& operator= (const Variable& other);
    virtual bool operator== (const Variable& other) const=0;
    virtual void print()=0;
};


#endif //ASSIN4_VARIABLE_H
