/*
 * main.cpp
 *
 *  Created on: Jan 8, 2018
 *      Author: ise
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <list>
#include "MyInt.h"
#include "MyBool.h"
#include "MyString.h"
#include "MyArray.h"
#include "VariableNotFoundException.h"
#include "BadVariableTypeException.h"

using namespace std;


/*The function check if c is
 * one of the separators
 */
bool Contains(char separator[4], char c)
{
    for (int i = 0; i < 4; i++)
    {
        if (separator[i] == c)
        {
            return true;
        }
    }
    return false;
}

/*
 * Split the line to tokens, spliters by the separators
 */
void Split(list<string>& lTokens, list<string>& lSplits, string line, char separator[4])
{
    while (line.length() > 0)
    {
        string sToken;
        unsigned int i = 0;
        for (i = 0; i < line.length(); i++)
        {
            if (Contains(separator, line[i]))
            {
                if (sToken.length() > 0)
                    lTokens.push_back(sToken);
                break;
            }
            else
                sToken += line[i];
        }
        if (i == line.length())
        {
            lTokens.push_back(sToken);
            line = "";
        }
        else
        {
            if (Contains(separator, line[i + 1]))
            {
                stringstream ss1;
                stringstream ss2;
                string s;
                string s1;
                string s2;
                char c1 = line[i];
                char c2 = line[i + 1];
                ss1 << c1;
                ss1 >> s1;
                ss2 << c2;
                ss2 >> s2;
                s = s1 + s2;
                lSplits.push_back(s);
                line = line.substr(i + 2);
            }
            else
            {
                stringstream ss;
                string s;
                char c = line[i];
                ss << c;
                ss >> s;
                lSplits.push_back(s);
                line = line.substr(i + 1);
            }
        }
    }
}


bool isNumber(string s)
{
    for (unsigned int i = 0; i < s.length(); i++)
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
        {
            return false;
        }
    }
    return true;
}


bool isBool(string s)
{
    if (strcmp(s.c_str(), "true") == 0 || strcmp(s.c_str(), "false") == 0)
        return true;
    return false;
}

bool isString(string s)
{
    if (s[0] == '"')
        return true;
    return false;
}

bool isArray(string s){
    if(s[0]== '[')
        return true;
    return false;
}

/*
 * check the current size of the array
 */
int currentSize(string s){
    int count=1;
	unsigned i=1;
    s=s.substr(1);
    while(i<s.length()-1){
        while(s[i]!=']'){
            if(s[i]==','){
                count++;
                i++;
            }
            else{
                i++;
            }
        }
    }
    return count;
}

/*
 * return the array name
 */
string arrayName(string s){
    string newString="";
    int i=0;
    while(s[i]!='['){
        newString= newString + s[i];
        i++;
    }
    return newString;
}


bool isArrayPos(string newName) {
    while(newName.length()>0)
    {
        if(newName[0]=='[')
            return true;
        newName=newName.substr(1);
    }
    return false;
}

/*
 * return the exact position int the array
 */
int arrayPos(string newName){
    string position="";
    int pos;
    while(newName.length()>0 && newName[0]!='['){
        newName=newName.substr(1);
    }
    if(newName[0]=='['){
        newName=newName.substr(1);
        while( newName[0]!=']'){
            position=position+newName[0];
            newName=newName.substr(1);
        }
    }

    string str = position;
    istringstream ( str ) >> pos;
    return pos;
}

/*
 * return the exact variable with the name- name, in the list
 */
Variable* existVar(const string& name,  list<Variable*>& lVariables)
{
    for (list< Variable *>::iterator it = lVariables.begin(); it != lVariables.end(); it++){
        	Variable* v = (Variable*)(*it);
        if (v->currentVar(name))
            return *it;
    }
    return NULL;
}

/*
 */
Variable* parseRecursively(list<Variable*>& lVariables, list<string>& lTokens, const list<string>& lSplits, std::list<string>::iterator itToken,
                           std::list<string>::iterator itSplit, Variable* var){
    Variable* temp = NULL;
    int pos;
    if (itSplit == lSplits.end())
    {
        return var;
    }
    string option = *(itSplit);
    Variable* newVar = NULL;

    if (option == "=")
    {
        string newName = *itToken;
        itToken++;

        if (isNumber(*itToken))
        {
            string myStream = *itToken;
            istringstream buffer(myStream);
            int value;
            buffer >> value;
            newVar = new MyInt(value, newName);
        }
        else if (isBool(*itToken))
        {
            string myStream = *itToken;
            bool value;
            if (*itToken == "true")
            {
                value = true;
            } else {
                value = false;
            }
            newVar = new MyBool(value, newName);
        }
        else if (isString(*itToken))
        {
            string value = *itToken;
            value = value.substr(1, value.length() - 2);
            newVar = new MyString(value, newName);
        }
        else if (isArray(*itToken))
        {
            int size= currentSize(*itToken);
            string line= *itToken;
            list<string> TokValues;
            list<string> SepValues;
            char separatorVar[]= {',', '[', ']',};

            Split(TokValues, SepValues, line, separatorVar);
            if(isNumber(*TokValues.begin())){
                newVar = new MyArray<MyInt>(size, newName, TokValues);
            }
            if(isString(*TokValues.begin())) {
                newVar = new MyArray<MyString>(size, newName, TokValues);
            }
            else if(isBool(*TokValues.begin())) {
                newVar = new MyArray<MyBool>(size, newName, TokValues);
            }
        }
        else if (isArrayPos(*itToken))
        {
            int pos= arrayPos(*itToken);
            string arrName= arrayName(*itToken);
            Variable* existVAR = existVar(arrName, lVariables);

            MyArray<MyInt> *ptIntArray = (dynamic_cast<MyArray<MyInt>*>(existVAR));
            if (ptIntArray != 0)
            {
                MyInt& m= ptIntArray->getValue(pos);
                newVar=&m;
            }
            MyArray<MyString> *ptStringArray = (dynamic_cast<MyArray<MyString>*>(existVAR));
            if (ptStringArray != 0)
            {
                MyString& m= ptStringArray->getValue(pos);
                newVar=&m;
            }
            MyArray<MyBool> *ptBoolArray = (dynamic_cast<MyArray<MyBool>*>(existVAR));
            if (ptBoolArray != 0)
            {
                MyBool& m= ptBoolArray->getValue(pos);
                newVar=&m;
            }
        }
        else
        {
            Variable *existRight = existVar(*itToken, lVariables);
            if (existRight != NULL)
            {
                const MyInt *ptInt = (dynamic_cast<const MyInt*>(existRight));
                const MyString *ptString = (dynamic_cast<const MyString *>(existRight));
                const MyBool *ptBool = (dynamic_cast<const MyBool*>(existRight));

                if (ptInt != 0)
                {
                    newVar = new MyInt(0, newName);
                    MyInt* myNewInt = (dynamic_cast<MyInt*>(newVar));
                    *myNewInt = *ptInt;
                }
                else if (ptString != 0)
                {
                    MyString *myNewString = new MyString("", newName);
                    *myNewString = *ptString;
                    newVar = myNewString;
                }
                else if (ptBool != 0)
                {
                    MyBool *myNewBool = new MyBool(false, newName);
                    *myNewBool = *ptBool;
                    newVar = myNewBool;
                }
            }
            else
            {
                throw VariableNotFoundException();
            }
        }
        if(isArrayPos(newName))
        {
            pos= arrayPos(newName);
            newName= arrayName(newName);
        }
        Variable* existLeft = existVar(newName, lVariables);
        if (existLeft == NULL)
        {
            lVariables.push_back(newVar);
        }
        else
        {
            MyInt* ptInt = (dynamic_cast<MyInt*>(existLeft));
            if (ptInt != 0)
            {
                *ptInt = *newVar;
            }
            MyString* ptString = (dynamic_cast<MyString*>(existLeft));
            if (ptString != 0)
            {
                *ptString = *newVar;
            }
            MyBool *ptBool = (dynamic_cast<MyBool*>(existLeft));
            if (ptBool != 0)
            {
                *ptBool = *newVar;
            }
            MyArray<MyInt> *ptIntArray = (dynamic_cast<MyArray<MyInt>*>(existLeft));
            if (ptIntArray != 0)
            {
                MyInt& m= ptIntArray->getValue(pos);
                m = (*newVar);
            }
            MyArray<MyString> *ptStringArray = (dynamic_cast<MyArray<MyString>*>(existLeft));
            if (ptStringArray != 0)
            {
                MyString& m= ptStringArray->getValue(pos);
                m = (*newVar);
            }
            MyArray<MyBool> *ptBoolArray = (dynamic_cast<MyArray<MyBool>*>(existLeft));
            if (ptBoolArray != 0)
            {
                MyBool& m= ptBoolArray->getValue(pos);
                m = (*newVar);
            }
        }
    }
    else if (option == "+")
    {
        int posLeft, posRight;
        bool isArrayRight=false;
        bool isArrayLeft=false;
        MyInt* newMyInt = NULL;
        string leftToken = "";
        Variable* existLeft = NULL;
        if (var == NULL)
        {
            leftToken = *itToken;
            if(isArrayPos(leftToken))
            {
                posLeft= arrayPos(leftToken);
                leftToken= arrayName(leftToken);
                isArrayLeft=true;
            }
            existLeft = existVar(leftToken, lVariables);
            itToken++;
        }

        if (isNumber(*itToken))
        {
            string myStream = *itToken;
            istringstream buffer(myStream);
            int value;
            buffer >> value;
            newMyInt = new MyInt(value, "");
        }
        else if (isArrayPos(*itToken))
        {
            posRight= arrayPos(*itToken);
            string arrNameRight= arrayName(*itToken);
            Variable* existRight = existVar(arrNameRight, lVariables);

            MyArray<MyInt> *ptIntIntArray = (dynamic_cast<MyArray<MyInt>*>(existRight));
            if (ptIntIntArray != 0)
            {
                MyInt& m= ptIntIntArray->getValue(posRight);
                newMyInt = &m;
            }
        }
        else
        {
            Variable* existRight = existVar(*itToken, lVariables);
            if (existRight != NULL) {
                newMyInt = new MyInt(*(dynamic_cast<MyInt*>(existRight)));
                if (newMyInt == 0) {
                    throw BadVariableTypeException();
                }
            }
            else
            {
                throw VariableNotFoundException();
            }
        }
        MyInt* newTempInt = new MyInt(0, "");
        if (existLeft == NULL) {
            if (var != NULL)
            {
                MyInt* tempInt = (dynamic_cast<MyInt*>(var));
                if (tempInt != 0)
                {
                    *newTempInt = *tempInt + *newMyInt;
                    temp = newTempInt;
                    delete(tempInt);
                    delete(newMyInt);
                }
                else
                {
                    throw VariableNotFoundException();
                }
            }
            else
            {
                string myStream = leftToken;
                istringstream buffer(myStream);
                int value;
                buffer >> value;
                MyInt* tempInt = new MyInt(value, "");
                *newTempInt = *tempInt + *newMyInt;
                temp = newTempInt;
                delete(tempInt);
                delete(newMyInt);
            }
        }
        else
        {
            MyInt* ptInt = (dynamic_cast<MyInt*>(existLeft));
            if (ptInt != 0)
            {
                ptInt = new MyInt(*(dynamic_cast<MyInt*>(existLeft)));
                *newTempInt = *ptInt + *newMyInt;
                temp = newTempInt;
                delete(newMyInt);
                delete(ptInt);
            }
            MyArray<MyInt> *ptArray = (dynamic_cast<MyArray<MyInt>*>(existLeft));
            if (ptArray != 0)
            {
                MyInt& m = ptArray->getValue(posLeft);
                *newTempInt = m + *newMyInt;
                temp = newTempInt;
                delete(newMyInt);
            }
        }
    }
    else if (option == "+=")
    {
        int pos, posRight;
        MyInt* newMyInt = NULL;
        string leftToken = "";
        Variable* existLeft = NULL;
        if (var == NULL)
        {
            leftToken = *itToken;
            if(isArrayPos(leftToken))
            {
                pos = arrayPos(leftToken);
                leftToken = arrayName(leftToken);
            }
            existLeft = existVar(leftToken, lVariables);
            itToken++;
        }

        if (existLeft != NULL)
        {
            if (isNumber(*itToken))
            {
                string myStream = *itToken;
                istringstream buffer(myStream);
                int value;
                buffer >> value;
                newMyInt = new MyInt(value, "");
            }
 			else if (isArrayPos(*itToken))
            {
                posRight= arrayPos(*itToken);
                string arrNameRight= arrayName(*itToken);
                Variable* existRight = existVar(arrNameRight, lVariables);

                MyArray<MyInt> *ptIntIntArray = (dynamic_cast<MyArray<MyInt>*>(existRight));
                if (ptIntIntArray != 0)
                {
                    MyInt& m= ptIntIntArray->getValue(posRight);
                    newMyInt=&m;
                }
            }
            else
            {
                Variable* existRight = existVar(*itToken, lVariables);
                if (existRight != NULL) {
                    newMyInt = new MyInt(*(dynamic_cast<MyInt*>(existRight)));
 					if (newMyInt == 0) {
                        throw BadVariableTypeException();
                    }
                }
                else
                {
                    throw VariableNotFoundException();
                }
            }

            if(newMyInt != NULL)
            {
                MyInt* tempInt = (dynamic_cast<MyInt*>(existLeft));
                MyArray<MyInt>* ptArray = (dynamic_cast<MyArray<MyInt>*>(existLeft));

                if (tempInt != 0)
                {
                    *tempInt += *newMyInt;
                    temp = tempInt;
                    delete(newMyInt);
                }
                else if (ptArray != 0)
                {
                    MyInt& m = ptArray->getValue(pos);
                    m += (*newMyInt);
                    temp = &m;
                    delete(newMyInt);
                }
                else
                {
                    throw VariableNotFoundException();
                }
            }
        }
    }
    else if (option == "==")
    {
        int pos;
        bool res = false;
        bool isArray = false;
        string leftToken = "";
        Variable* existLeft = NULL;
        if (var == NULL)
        {
            leftToken = *itToken;
            if(isArrayPos(leftToken))
            {
                pos= arrayPos(leftToken);
                leftToken= arrayName(leftToken);
                isArray=true;
            }
            existLeft = existVar(leftToken, lVariables);
            itToken++;
        }
        //if (leftToken != lTokens.back())
        //  itToken++;

        if (isNumber(*itToken))
        {
            MyInt* newMyInt = NULL;
            string myStream = *itToken;
            istringstream buffer(myStream);
            int value;
            buffer >> value;
            newMyInt = new MyInt(value, "");
            MyInt* tempInt;
            Variable* existLeft = existVar(leftToken, lVariables);
            if (var != NULL)
            {
                tempInt = (dynamic_cast<MyInt*>(var));
            }
            else if (existLeft != 0)
            {
                if(isArray)
                {
                    MyArray<MyInt> *ptArray = (dynamic_cast<MyArray<MyInt>*>(existLeft));
                    if (ptArray != 0)
                    {
                        MyInt& m = ptArray->getValue(pos);
                        bool ans = (m == (*newMyInt));
                        tempInt = &m;
                    }
                }
                else
                {
                    tempInt = new MyInt(*(dynamic_cast<MyInt*>(existLeft)));
                }
            }
            else
            {
                string myStream = leftToken;
                istringstream buffer(myStream);
                int value;
                buffer >> value;
                tempInt =  new MyInt(value, "");
            }
            res = (*tempInt == *newMyInt);
            delete(newMyInt);
            delete(tempInt);
        }
        else if (isBool(*itToken))
        {
            bool value;
            if (*itToken == "true")
            {
                value = true;
            }
            else
            {
                value = false;
            }
            MyBool newMyBool(value, "");
            MyBool* tempBool;
            Variable* existLeft = existVar(leftToken, lVariables);
            if (var != NULL)
            {
                tempBool = (dynamic_cast<MyBool*>(var));
            }
            else if (existLeft != 0)
            {
                tempBool = new MyBool(*(dynamic_cast<MyBool*>(existLeft)));
            }
            else
            {
                if (leftToken == "true")
                {
                    value = true;
                }
                else
                {
                    value = false;
                }
                tempBool = new MyBool(value, "");
            }
            res = (*tempBool == newMyBool);
            delete(tempBool);
        }
        else if (isString(*itToken))
        {
            string value = *itToken;
            value = value.substr(1, value.length() - 2);
            MyString newMyString(value, "");
            MyString* tempString;
            Variable* existLeft = existVar(leftToken, lVariables);
            if (var != NULL)
            {
                tempString = (dynamic_cast<MyString*>(var));
            }
            else if (existLeft != 0)
            {
                tempString = new MyString(*(dynamic_cast<MyString*>(existLeft)));
            }
            else
            {
                value = leftToken;
                value = value.substr(1, value.length() - 2);
                tempString = new MyString(value, "");
            }
            res = (*tempString == newMyString);
            delete(tempString);
        }
        else if (isArrayPos(*itToken))
        {
            int pos = arrayPos(*itToken);
            leftToken = arrayName(*itToken);
            MyInt *newMyInt;
            //isArray=true;
            Variable* existRight = existVar(leftToken, lVariables);

            MyArray<MyInt> *ptArray = (dynamic_cast<MyArray<MyInt>*>(existRight));
            if (ptArray != 0)
            {
                MyInt& m = ptArray->getValue(pos);
                int value = m.getValue();
                newMyInt = new MyInt(value, "");
            }
            MyInt* tempInt;
            Variable* existLeft = existVar(leftToken, lVariables);
            if (var != NULL)
            {
                tempInt = (dynamic_cast<MyInt*>(var));
            }
            else if (existLeft != 0)
            {
                tempInt = new MyInt(*(dynamic_cast<MyInt*>(existLeft)));
            }

            res = (*tempInt == *newMyInt);
            delete(newMyInt);
            delete(tempInt);
        }
        else
        {
            Variable* existRight = existVar(*itToken, lVariables);
            if (existRight != NULL)
            {
                Variable* existLeft = existVar(leftToken, lVariables);
                if (var != NULL)
                {
                    const MyInt *ptInt = (dynamic_cast<const MyInt*>(var));
                    if (ptInt != 0)
                    {
                        res = (*ptInt == *existRight);
                    }
                    const MyString* ptString = (dynamic_cast<const MyString*>(var));
                    if (ptString != 0)
                    {
                        res = (*ptString == *existRight);
                    }
                    const MyBool* ptBool = (dynamic_cast<const MyBool*>(var));
                    if (ptBool != 0)
                    {
                        res = (*ptBool == *existRight);
                    }
                }
                else if (existLeft != NULL)
                {
                    MyInt* ptInt = (dynamic_cast<MyInt*>(existLeft));
                    if (ptInt != 0)
                    {
                        res = (*ptInt == *existRight);
                    }
                    MyString* ptString = (dynamic_cast<MyString*>(existLeft));
                    if (ptString != 0)
                    {
                        res = (*ptString == *existRight);
                    }
                    MyBool *ptBool = (dynamic_cast<MyBool*>(existLeft));
                    if (ptBool != 0)
                    {
                        res = (*ptBool == *existRight);
                    }
                }
                else
                {
                    if (isNumber(leftToken))
                    {
                        string myStream = leftToken;
                        istringstream buffer(myStream);
                        int value;
                        buffer >> value;
                        MyInt newTempInt(value, "");
                        res = (newTempInt == *existRight);
                    }
                    else if (isBool(leftToken))
                    {
                        bool value;
                        if (leftToken == "true")
                        {
                            value = true;
                        }
                        else
                        {
                            value = false;
                        }
                        MyBool newTempBool(value, "");
                        res = (newTempBool == *existRight);
                    }
                    else if (isString(leftToken))
                    {
                        string value = leftToken;
                        value = value.substr(1, value.length() - 2);
                        MyString newTempString(value, "");
                        res = (newTempString == *existRight);
                    }
                    else
                    {
                        throw BadVariableTypeException();
                    }
                }
            }
            else
            {
                throw VariableNotFoundException();
            }
        }
        MyBool* newTempBool = new MyBool(res, "");
        temp = newTempBool;
    }
    else if (option == ")")
    {
        if (var == NULL)
        {
            if (isNumber(*itToken))
            {
                string myStream = *itToken;
                istringstream buffer(myStream);
                int value;
                buffer >> value;
                temp = new MyInt(value, "");
            }
            else if (isBool(*itToken))
            {
                bool value;
                if (*itToken == "true")
                {
                    value = true;
                }
                else
                {
                    value = false;
                }
                temp = new MyBool(value, "");

            }
            else if (isString(*itToken))
            {
                string value = *itToken;
                value = value.substr(1, value.length() - 2);
                temp = new MyString(value, "");
            }
            else if (isArrayPos(*itToken))
            {
                int pos= arrayPos(*itToken);
                string arrName= arrayName(*itToken);
                MyInt *newMyInt;
                MyString *newMyString;
                MyBool *newMyBool;
                Variable* existVAR = existVar(arrName, lVariables);

                MyArray<MyInt> *ptIntArray = (dynamic_cast<MyArray<MyInt>*>(existVAR));
                if (ptIntArray != 0)
                {
                    MyInt& m = ptIntArray->getValue(pos);
                    int value = m.getValue();
                    temp = new MyInt(value, "");
                }
                MyArray<MyString> *ptStringArray = (dynamic_cast<MyArray<MyString>*>(existVAR));
                if (ptStringArray != 0)
                {
                    MyString& m = ptStringArray->getValue(pos);
                    string value = m.getValue();
                    temp = new MyString(value, "");
                }
                MyArray<MyBool> *ptBoolArray = (dynamic_cast<MyArray<MyBool>*>(existVAR));
                if (ptBoolArray != 0)
                {
                    MyBool& m = ptBoolArray->getValue(pos);
                    bool value = m.getValue();
                    temp = new MyBool(value, "");
                }
            }
            else
            {
                Variable* existRight = existVar(*itToken, lVariables);
                if (existRight != NULL)
                {
                    temp = existRight;
                }
                else
                {
                    throw VariableNotFoundException();
                }
            }
        }
        else
        {
            temp = var;
        }
    }
    itSplit++;
    itToken++;
    Variable* returnVar = parseRecursively(lVariables, lTokens, lSplits, itToken, itSplit, temp);

    return returnVar;
}



void makeIfParts(string line, list<string>&lTokensTermLine,list<string> &lSplitsTermLine,
                 list<string>&lTokensDoLine, list<string>&lSplitsDoLine,
                 list<string>&lTokensElseLine, list<string>&lSplitsElseLine, char separator[4]){
    string TermLine="";
    string DoLine="";
    string ElseLine="";
    int i=0;
    while(line.length()>0 && line[i]!='(') {
        i++;
    }
    line= line.substr(i+1);

    i=0;
    while(line.length()>0 && line[i]!=')'){
        TermLine=TermLine+line[i];
        i++;
    }
    line= line.substr(i+1);


    if(line.length()>0)
        if(line[0]=='{')
            line=line.substr(1);

    i=0;
    while(line.length()>0 && line[i]!='}'){
        DoLine=DoLine+line[i];
        i++;
    }
    if(line.length()>0){
        line= line.substr(i+1);}

    if(line.length()>0) {
        i=0;
        while(line.length()>0 && line[i]!='{') {
            i++;
        }
        line= line.substr(i+1);
        i = 0;
        while (line.length() > 0 && (line[i] != '}')&&(line[i] != '{')) {
            ElseLine=  ElseLine + line[i];
            i++;
        }
        line= line.substr(i+1);
    }

    Split(lTokensTermLine, lSplitsTermLine, TermLine, separator);
    Split(lTokensDoLine, lSplitsDoLine, DoLine, separator);
    Split(lTokensElseLine, lSplitsElseLine, ElseLine, separator);

}


int main() {
    ifstream myReadFile;
    char separator[] = {'+', '=', '(', ')'};
    list<Variable *> lVariables;
    string line;
    string file;
    cin >> file;
    const char* fileName= file.c_str();
    myReadFile.open(fileName);
    if (myReadFile.is_open()) {
        list<string> lTokens;
        list<string> lSplits;
        while (!myReadFile.eof()) {
            lTokens.clear();
            getline(myReadFile, line);
            lSplits.clear(); // Saves the line in STRING.
            if (line.empty()) {
                continue;
            }
            Split(lTokens, lSplits, line, separator);
            //for (list<string>::iterator it = lTokens.begin(); it != lTokens.end(); it++)
            //    cout << *it << " lTokens "<< "\n";
            std::list<string>::iterator itSplit;
            std::list<string>::iterator itToken;
            itSplit = lSplits.begin();
            itToken = lTokens.begin();
            string option = *(itSplit);


            if (*itToken == "print")
            {
                itToken++;
                itSplit++;
                Variable* varToPrint = parseRecursively(lVariables, lTokens, lSplits, itToken, itSplit, NULL);
                varToPrint->print();
                cout<< "\n";
            }

            else if(*itToken == "if")
            {
                bool res=false;

                list<string> lTokensTermLine, lSplitsTermLine, lTokensDoLine, lSplitsDoLine, lTokensElseLine, lSplitsElseLine;
                makeIfParts(line, lTokensTermLine, lSplitsTermLine, lTokensDoLine, lSplitsDoLine,  lTokensElseLine, lSplitsElseLine, separator);
                itSplit = lSplitsTermLine.begin();
                itToken = lTokensTermLine.begin();

                Variable* varIfTerm = parseRecursively(lVariables, lTokensTermLine, lSplitsTermLine, itToken, itSplit, NULL);

                const MyBool *ptBool= (dynamic_cast<const MyBool*>(varIfTerm));
                if(ptBool!=0){
                    res= ptBool->getValue();
                }
  				else{
                    throw BadVariableTypeException();
                }

                if(res==true){
                    itSplit = lSplitsDoLine.begin();
                    itToken = lTokensDoLine.begin();

                    if (*itToken == "print")
                    {
                        itToken++;
                        itSplit++;
                        Variable* varToPrint = parseRecursively(lVariables, lTokensDoLine, lSplitsDoLine, itToken, itSplit, NULL);
                        varToPrint->print();
                    }
                    else {
                        Variable *varIfTerm = parseRecursively(lVariables, lTokensDoLine, lSplitsDoLine, itToken,
                                                               itSplit, NULL);
                    }
                }

                if(res==false && lTokensElseLine.begin()!=lTokensElseLine.end()){
                    itSplit = lSplitsElseLine.begin();
                    itToken = lTokensElseLine.begin();

                    if (*itToken == "print")
                    {
                        itToken++;
                        itSplit++;
                        string c= *itSplit;
                        Variable* varToPrint = parseRecursively(lVariables, lTokensElseLine, lSplitsElseLine, itToken, itSplit, NULL);
                        varToPrint->print();
                    }
                    else {
                        Variable *varIfTerm = parseRecursively(lVariables, lTokensElseLine, lSplitsElseLine, itToken,
                                                               itSplit, NULL);
                    }
                }
            }
            else
            {
                Variable* v = parseRecursively(lVariables, lTokens, lSplits, itToken, itSplit, NULL);
            }
        }

        for (list< Variable *>::iterator  it = lVariables.begin(); it != lVariables.end(); it++) {
            Variable *v = (*it);
            if(v!=NULL)
                delete (v);
        }
        myReadFile.close();
        return 0;
    }
}
