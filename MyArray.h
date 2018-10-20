//
// Created by ise on 16/01/18.
//

#ifndef ASSIN4_MYARRAY_H
#define ASSIN4_MYARRAY_H

#include <iostream>
#include "Variable.h"
#include <list>
#include "MyInt.h"
#include "MyBool.h"
#include "MyString.h"
#include "BadVariableTypeException.h"
#include "ArrayOutOfBoundException.h"

using namespace std;

/* MyArray is generic - it has array- it can be MyInt, MyString or MyBool array.
 *  It has a size, Variable methods and more methods.
 */
template <class T>
class MyArray : public Variable
{
private:
    int m_size;
    T* m_array;

public:
    MyArray(int size, string name, list<string> values):Variable(name),m_size(size){
        m_array = new T[size];
        insertValues(values);
    }

    virtual ~MyArray() {
        // delete(m_array);
    }

    T& getValue (int indx){
        if(indx>=m_size){
            throw ArrayOutOfBoundException();
        }
        return m_array[indx];
    }

    bool operator== (const Variable& other) const{
        return false;
    }

    virtual void print(){
        for(int i=0; i<this->m_size; i++){
            (this->m_array[i]).print();
            if(i!=this->m_size-1)
                cout<< ',' ;
        }
        cout<< '\n' ;

    }

    void insertValues(list<string> values)
    {
        int i=0;
        for (list<string>::iterator it = values.begin(); it != values.end(); it++) {
            T * newVar = new T(*it, "");
            m_array[i]= *newVar;
            delete(newVar);
            i++;}
    }


};



#endif //ASSIN4_MYARRAY_H
