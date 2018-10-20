//
// Created by ise on 13/01/18.
//

#ifndef ASSIN4_MYBOOL_H
#define ASSIN4_MYBOOL_H

#include <iostream>
#include "Variable.h"

using namespace std;


/* MyBool a a kind of Variable.
 *  It has m_value and operators that are virtual (MyBool has own operators).
 */
class MyBool : public Variable
{
private:
    bool m_value;

public:
    MyBool();
    MyBool(bool value, string name);
    MyBool(string value, string name);
    virtual ~MyBool();

    bool setValue(bool value);
    bool getValue()const;
    virtual Variable& operator= (const Variable& other);
    virtual bool operator== (const Variable& other) const;
    virtual void print();
};

#endif //ASSIN4_MYBOOL_H
