//
// Created by ise on 13/01/18.
//

#include "MyInt.h"
#include <sstream>
using namespace std;

MyInt::MyInt():Variable(""),m_value(0){}

MyInt::MyInt(int value, string name):Variable(name),m_value(value){}

MyInt::MyInt(string value, string name):Variable(name){
    string str = value;
    istringstream ( str ) >> m_value;
}

MyInt::~MyInt(){}

int MyInt::getValue()const{
    return this->m_value;
}


MyInt MyInt::operator+ (const Variable& other) const{
    MyInt myint(1, "");
    const MyInt *ptInt= (dynamic_cast<const MyInt*>(&other));
    if(ptInt!=0)
    {
        myint.m_value = this->m_value + ptInt->m_value;
    }
    else
    {
        throw BadVariableTypeException();
    }
    return myint;
}

Variable& MyInt::operator= (const Variable& other){
    const MyInt *ptInt= (dynamic_cast<const MyInt*>(&other));
    if(ptInt!=0){
        this->m_value= ptInt->m_value;}
    else{
        throw BadVariableTypeException();
    }
    return *(dynamic_cast<Variable*>(this));
}

MyInt& MyInt::operator+= (const Variable& other){
    const MyInt *ptInt= (dynamic_cast<const MyInt*>(&other));
    if(ptInt!=0){
        this->m_value= this->m_value + ptInt->m_value;}
    else
    {
        throw BadVariableTypeException();
    }
    return *this;
}

bool MyInt::operator== (const Variable& other) const{
    const MyInt *ptInt= (dynamic_cast<const MyInt*>(&other));
    if(ptInt!=0){
        if(this->m_value== ptInt->m_value)
            return true;
    }
    else{
        throw BadVariableTypeException();
    }
    return false;
}

void MyInt::print(){
    cout<<(this->m_value)<< " ";
}