//
// Created by ise on 13/01/18.
//


#include "MyString.h"

MyString::MyString():Variable(""),m_value(""){}

MyString::MyString(string value, string name):Variable(name),m_value(value){}

MyString::~MyString(){}

string MyString::getValue()const{
    return this->m_value;
}

string MyString::setValue(string value){
    this->m_value=value;
}

Variable & MyString::operator= (const Variable& other){
    const MyString *ptString= (dynamic_cast<const MyString*>(&other));
    if(ptString!=0)
    {
        this->m_value = ptString->m_value;
    }
    else
    {
        throw BadVariableTypeException();
    }
    return *(dynamic_cast<Variable*>(this));
}

bool MyString::operator== (const Variable& other) const{
    const MyString *ptString= (dynamic_cast<const MyString*>(&other));
    if(ptString!=0){
        if(this->m_value== ptString->m_value)
            return true;
    }
    else
    {
        throw BadVariableTypeException();
    }
    return false;
}

void MyString::print(){
    cout<<(this->m_value)<<" ";
}