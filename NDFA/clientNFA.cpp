/**************************************************************************

Name: Omid Azodi
Professor: Dr. Guillen
Due Date: 04/03/2017
Class: CS421 Theory of Computing
Assignment: Programming Assignment #1

Description of Project:
Identify email messages that are spam email given a collection of emails.
Must design and implement an Finite Automata that accepts strings in the language.

L = { w= "free access", w= "free software", w= "free vacation", w= "free trials"
      w= "win", w= "winner", w= "winners", w= "winnings" }

The strings must be read from the body of the email no where else.
The words may or may not have these strings within quotes. Must accept both with and without quotes.

SIMULATE Finite Automata by reading (ONE input symbol) and display state the Finite Automata reaches.

File Name: clientNFA.cpp
Description of File: Create the NFA object and call corresponding functions part of NFA to print out desired results of processed emails

All file names:
1) NFA.h
2) NFA.cpp
3) clientNFA.cpp
4) messagefile.txt

How to compile:
g++ *.cpp 
or
g++ NFA.cpp clientNFA.cpp 
or
g++ *.cpp -o AzodiOmid

How to run:
./a.out
or 
./AzodiOmid

Compiler: g++ compiler provided on empress server
README.txt provided as well
***************************************************************************************************************************/

#include "NFA.h" //includes all libraries required and NFA class

int main()
{
  vector<char> emailFile; //used to store symbols character by character from file
  NFA emailChecker;//object of NFA class to make desired function calls and process
  emailChecker.openEmailFile();//opens the file "messagefile.txt" can not change file name 
  
  emailChecker.readFile(emailFile);//reads all symbols from file one at a time and stored into vector
  emailChecker.processSymbol(emailFile);//process each symbol from file individually from the vector

  emailChecker.printFinalEmailTableFormat();//print final result of msgID's that are spam at end in a nice table format

  return 0;

}//end of main function implementation
