/**********************************************************************************
Name: Omid Azodi
Professor: Dr. Guillen
Class: CS421 Theory of Computing
Due Date: 05/08/2017

File Name: pda.h

Description: Creates Push Down Automata Simulating Class with necessary functionaility
**********************************************************************************/

#ifndef PDA_H
#define PDA_H

//Necessary libraries 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <stack>//used for PDA stack
 
using namespace std;

class PDA
{
 protected:
  //stack where alphabet will be pushed if needed
  stack<char> myStack;
  
 public:
  //default constructor
  PDA();
  //default de-structor
  ~PDA();
  /*readFile will read from input file and store into vector ready to be parsed*/
  void readFile(vector<char>& pdaContent);
  /*printFile will print everything store in vector from input file*/
  void printFile(vector<char> pdaContent);
  /*parser will parse through line by line from vector and display result*/
  void parser(vector<char> pdaContent);
  /*printStack what is in stack of PDA, for debugging purposes & visual*/
  void printStack(stack<char> myStack);
  /*clearStack will clear all stack of PDA for new line to be parsed*/ 
  void clearStack(stack<char>& myStack);
  /*replace will take new input and replace top of stack*/
  void replace(stack<char>& myStack, char newOne);
  /*printResult will take result from parser function and display the message*/
  void printResult(bool result);
};

#endif
