/*
 * MyBool.cpp
 *
 *  Created on: Jan 8, 2018
 *      Author: ise
 */

#include "MyBool.h"

MyBool::MyBool():Variable(""),m_value(false){}

MyBool::MyBool(bool value, string name):Variable(name),m_value(value){}

MyBool::MyBool(string value, string name):Variable(name){
    if(value=="false")
    {
       m_value=false;
    }
    else
    {
        m_value=true;
    }

}

MyBool::~MyBool(){}

bool MyBool::getValue()const{
    return this->m_value;
}


Variable & MyBool::operator= (const Variable& other){
    const MyBool *ptBool= (dynamic_cast<const MyBool*>(&other));
    if(ptBool!=0){
        this->m_value= ptBool->m_value;}
    else
    {
        throw BadVariableTypeException();
    }
    return *(dynamic_cast<Variable*>(this));
}

bool MyBool::operator== (const Variable& other) const{
    const MyBool *ptBool= (dynamic_cast<const MyBool*>(&other));
    if(ptBool!=0){
        if(this->m_value== ptBool->m_value)
            return true;
    }
    else
    {
        throw BadVariableTypeException();
    }
    return false;
}

void MyBool::print(){
    if (this->m_value == false)
        cout << "false " ;
    else
        cout << "true " ;
}