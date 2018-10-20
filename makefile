scriptRunner: Variable.o MyString.o MyBool.o MyInt.o MyArray.o main.o 
	g++  Variable.o MyString.o MyBool.o MyInt.o MyArray.o main.o  -o scriptRunner

Variable.o: Variable.cpp Variable.h 
	g++  -c  Variable.cpp

MyString.o: MyString.cpp MyString.h Variable.h
	g++  -c  MyString.cpp

MyBool.o: MyBool.cpp MyBool.h Variable.h
	g++  -c  MyBool.cpp

MyInt.o: MyInt.cpp MyInt.h Variable.h
	g++  -c  MyInt.cpp

MyArray.o: MyArray.h MyInt.h MyBool.h  MyString.h Variable.h ArrayOutOfBoundException.h BadVariableTypeException.h
	g++  -c  MyArray.cpp

main.o: main.cpp MyInt.h MyBool.h  MyString.h MyArray.h VariableNotFoundException.h BadVariableTypeException.h
	g++  -c  main.cpp
clean: 
	rm -f *.o


