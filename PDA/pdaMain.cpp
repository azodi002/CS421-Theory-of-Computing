/************************************************************************
Name: Omid Azodi
Professor: Dr. Guillen
Class: CS421 Theory of Computing
Due Date: 05/08/2017

File Name: pdaMain.cpp

Total file names: 
1) pda.h
2) pda.cpp
3) pdaMain.cpp

How to Compile: 
g++ pda.cpp pdaMain.cpp
or
g++ pda.cpp pdaMain.cpp -o AzodiOmid
or
g++ *.cpp (preferred way of compiling, and generates a.out)

How to Run:
./a.out
or
./AzodiOmid

Description:
Implement a parser that processes sequences of correctly paired if and else 
in C++ program. There can be if without else, but not else without if.
if may appear within blocks and parser must pair with else(s). 
Simulates a PDA:
Using transition functions & Stack
***********************************************************************/ 

#include "pda.h"

int main(int argc, char* argv[])
{
  PDA conditionChecker;
  
  //holds all file contents
  vector<char> pdaContent;
  
  //stack that simulates PDA
  stack<char> myStack;
  
  //all sequence.txt stored in pdaContent
  conditionChecker.readFile(pdaContent);
  
  //parses line by line until new line is reached and displays accepted or not accepted 
  conditionChecker.parser(pdaContent);

  return 0;
}
