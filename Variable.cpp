//
// Created by ise on 13/01/18.
//

#include "Variable.h"

Variable::~Variable(){}


Variable& Variable::operator= (const Variable& other){
    return *this;
}

bool Variable::currentVar (string name){
    if(this->m_name==name)
        return true;
    return false;
}

string Variable::getName()const{
    return this->m_name;
}
