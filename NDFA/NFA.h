/************************************************************************************************************************

Name: Omid Azodi
Due Date: 04/03/2017
Class: CS421 Theory of Computing
Professor. Dr. Guillen
Project: Programming Assignment #1

Description of Project:
Identify email messages that are spam email given a collection of emails.
Must design and implement an Finite Automata that accepts strings in the language.

L = { w= "free access", w= "free software", w= "free vacation", w= "free trials"
      w= "win", w= "winner", w= "winners", w= "winnings" }

The strings must be read from the body of the email no where else.
The words may or may not have these strings within quotes. Must accept both with and without quotes.

SIMULATE Finite Automata by reading (ONE input symbol) and display state the Finite Automata reaches.

File Name: NFA.h
Description of File: Create Non-Deterministic Finite Automata (NFA/NDFA), with functions to compute and process symbols.

**********************************************************************************************************************/

#include <iostream> //cout/cin
#include <string> //string
#include <vector> //vector 
#include <fstream> //input file stream
#include <algorithm> //sort function vector 
using namespace std;

/**************************************************************************************
Goal of NFA class is to simulate the finite automata.
Has member variables and functions to help determien states and transitions.
Used to abstract detail implementation from client, and making client file much easier
***************************************************************************************/
class NFA
{
 private:
  ifstream inFile; //Associated message file for NFA to process
  vector<char> file; //the file being processed
  vector<string> msgID; //stores all msgID of emails
  vector<string> spam; //stores all msgID that is spam
  static int state; //state of finite automata
 
 public:
  NFA();
  ~NFA();
  void openEmailFile();//opens file of messagefile.txt (can not change file name)
  void printFinalEmailTableFormat();//prints final result of spam messages at end of output
  void readFile(vector<char>& file);//read and store symbols into vector 
  void processSymbol(vector<char> file);//process one symbol from email
  void incrementState();//used to determine and increment state of machine
  void resetStateForNewEmail();//used when new email has been read to reset state
  void printCurrentState(int state);//used to decide and print the current state of machine
  void printAllMessageID();//used for testing to print all msgID's found in email
};

