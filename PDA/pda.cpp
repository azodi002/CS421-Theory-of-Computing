/*****************************************************************
Name: Omid Azodi
Professor: Dr. Guillen
Class: CS421 Theory of Computing
Due Date: 05/08/2017

File Name: pda.cpp
Description: Implementation of functions in PDA class
******************************************************************/
#include "pda.h"

//Default constructor 
PDA::PDA()
{
  cout << "Constructor called" << endl << endl;
}

//Default Destructor 
PDA::~PDA()
{
  cout << "Destructor called" << endl << endl;
}

/******************************
Input: vector pass by reference
Description of function: 
Will read from input file specifically named sequence.txt and store in vector
*******************************/ 
void PDA::readFile(vector<char>& pdaContent)
{
  
  ifstream inFile;
  //input file with statements must be named sequence.txt
  inFile.open("sequence.txt");
  char sequence;

  //go through character at a time from input file
  while(inFile.get(sequence))
    {
      //store each character including new line into vector
      pdaContent.push_back(sequence);
    }
  //push new line so last line can be parsed
  pdaContent.push_back('\n');
}

/***********************************************
Input: vector of input file
Desription:
Will print the vector of contents from input file
************************************************/
void PDA::printFile(vector<char> pdaContent)
{
  //iterator to go through file
  vector<char>::iterator it = pdaContent.begin(); 
  
  cout << endl; //Aesthetic purposes
  //go through file until end of file
  for(;it!=pdaContent.end();it++)
    {
      cout << *it;
    }
}

/********************************************************************
Input: vector of input file
Description:
Will go through each line of input file character by character and
display final result whether it sequence was accepted or not
********************************************************************/ 
void PDA::parser(vector<char> pdaContent)
{
  vector<char>::iterator it = pdaContent.begin();

  //PDA stack
  stack<char> myStack;
  //start symbol of z on stack
  myStack.push('z');
  
  //determines whether sequence was syntactically correct or not
  bool accepted = false;

  //states from transition function
  int state = 0;
  
  //will print sequence of character to user
  string parsedLine = "";

  //counts open and closed braces
  int open=0;
  int close=0;
  
  int counter = 0;

  //Loop to go through character at a time and determine state, and push, pop, transition
  for(;it!=pdaContent.end();it++)
    {
      accepted = false;

      //if not new line, meaning in same line
      if(*it!='\n')
	{
	  //if state is 0 and reads i and z on stack
      	  if(state == 0 && *it == 'i' && myStack.top() == 'z')
	    {
	      //stay same state and push i
	      state = 0;
	      myStack.push('i');
	    }
	  //if i read and next is open brace
	  if(*it == 'i' && *(it + 1) == '{')
	    {
	      //trap state
	      state = 50;
	    }
	  //if space in sequence incorrect
	  if(*it == ' ') 
	    {
	      //trap state
	      state = 50;
	    }

	  //if reading two consecutive brackets 
	  if(*it == '{' && *(it + 1) == '{')
	    {
	      //Trap state
	      state = 50;
	    }
	  //if the very first of line is open brace or f incorrect
	  if(counter == 0 && (*it == '{' || *it == 'f'))
	    {
	      //beginning of new line is open brace
	      //trap state
	      state = 50;
	    }

	  //if close brace and open brace
	  if(*it == '}' && *(it + 1) == '{')
	    {
	      state = 50;
	    }
	  
	  //if state is 0, read an f and i on top
	  else if(state == 0 && *it == 'f' && myStack.top() == 'i')
	    {
	      //stay state 0
	      state = 0;
	      //push f
	      myStack.push('f');
	    }
	  
	  //if state is 0 and read i and top is f   
	  else if(state == 0 && *it == 'i' && myStack.top() == 'f')
	    {
	      //stay state 0 
	      state = 0; 
	      //push i
	      myStack.push('i');
	    }
	  //if state is 0 and read e and top f
	  else if(state == 0 && *it == 'e' && myStack.top() == 'f')
	    {
	      //state is 1
	      state = 1; 
	      //change top of f to e
	      replace(myStack, 'e');
	    }
	  
	  //if state is 1 and read l and top is e
	  else if(state == 1 && *it == 'l' && myStack.top() == 'e')
	    {
	      //stay in 1
	      state = 1;
	      //pop top of stack   
	      myStack.pop();
	    }
	  
	  //state is 1, read an s and top is i
	  else if(state == 1 && *it == 's' && myStack.top() == 'i')
	    {
	      //state is 1
	      state = 1;
	      //replace s with i
	      replace(myStack, 's');
	    }
	  
	  //state is 1 and read e and top is s
	  else if(state == 1 && *it == 'e' && myStack.top() == 's')
	    {
	      //transition to 0
	      state = 0;
	      //pop from stack
	      myStack.pop();
	    }

	  //state is 0 and read open brace top is f
	  else if(state == 0 && *it == '{' && myStack.top() == 'f')
	    {
	      //stay at state 0
	      state = 0;
	      //push open brace
	      myStack.push('{');
	    }
	  
	  //state is 0, read i and top is open brace
	  else if(state == 0 && *it == 'i' && myStack.top() == '{')
	    {
	      //stay at state 0
	      state = 0;
	      //push i
	      myStack.push('i');
	    }
	  
	  //state is 0, read close brace and top is f
	  else if(state == 0 && *it == '}' && myStack.top() == 'f')
	    {
	      //change to state 2
	      state = 2;
	      //pop stack
	      myStack.pop();
	    }
	  
	  /****************************************
            if{}else{}
	   ***************************************/
	  else if(state == 0 && *it == '{' && myStack.top() == 'z')
	    {
	      myStack.push('{');
	      state = 0;
	    }

	  /*****************Test*****************
             if{ifelse{if}}else
	  ***************************************/
	  else if(state == 0 && *it == '{' && myStack.top() == '{')
	    {
	      myStack.push('{');
	    }
	  
	  //if beginning of the line is e and top is z
  	  else if(*it == 'e' && myStack.top() == 'z')
            {
	      //"trap" state 
	      state = 50;
            }
	  //state is 2
	  if(state == 2)
	    {
	      //while in state 2
	      while(state == 2)
		{
		  //the top is open brace
		  if(myStack.top() == '{')
		    {
		      //pop the open brace
		      myStack.pop();
		      //transition back to state 0
		      state = 0;
		    }
		  //top is not open brace keep popping
		  else if(myStack.top() != '{')
		    {
		      //pop until reached open brace
		      myStack.pop();
		    }
		}//end of while
	    }//End of state 2


	 //For the if{ifelse} case pops bracket with bracket
	  else if(state == 0 && *it == '}' && myStack.top() == '{')
	   {
	     //pop the stack
	     myStack.pop();
	   }
	  
	  //count number of open braces
	  if(*it == '{')
	    {
	      open++;
	    }

	  //count number of close braces
	  if(*it == '}')
	    {
	      close++;
	    }
	    
	  //cout << "THIS: " << *it << endl;
	  //cout << state << endl;
	  counter++;
	  parsedLine = parsedLine + *it; //print line for result
	}//end if not \n
    
      //if the new line is read meaning sequence is done
     if(*it == '\n')
	{
	  /***************************************
           1. Check top stack & state print result
           2. Clear stack for new line to parse
           3. Push z on top of stack
	  ***************************************/

	  //unequal amount of open/close brackets
	  if(open!=close)
	    {
	      accepted = false;
	    }

	  else if(state == 0 && myStack.top() == 'f')
	    {
	      accepted = true;
	    }	  
	  
	  else if(state == 0 && myStack.top() == 'z')
	    {
	      accepted = true;
	    }	  

	  //print the sequence that was being processed
	  cout << parsedLine;
	  printResult(accepted);

	  //clear stack for new process of sequences
	  clearStack(myStack);
	  //push the stack symbol z for PDA
	  myStack.push('z');
	  /*reset all counters/states/etc*/

	  parsedLine = "";
	  state = 0;
	  open = 0;
	  close = 0;
	  counter = 0;
	}//end if \n
     
     //used for debugging purposes the printStack function
     // printStack(myStack);
 
    }//end for

}//End function

/*******************************************
Input: stack of PDA
Desription: print the contents of PDA stack
********************************************/
void PDA::printStack(stack<char> myStack)
{  
  //while stack is not empty keep printing
  while(!myStack.empty())
    {
      cout << "|" << myStack.top();
      myStack.pop();
    }
  cout << endl;
}

/******************************************
Input: stack of PDA
Description: pop everything from the stack
*******************************************/
void PDA::clearStack(stack<char>& myStack)
{
  //keep popping if stack not empty
  while(!myStack.empty())
    {
      myStack.pop();
    }
}

/***********************************************************
Input: stack of PDA, and new character to replace in stack
Description: replace the top of PDA stack
************************************************************/
void PDA::replace(stack<char>& myStack, char newOne)
{
  //pop the top of stack
   myStack.pop();
   //push new symbol
   myStack.push(newOne);
}

/*********************************************************************************
Input: boolean of whether the sequence was accepted or not
Description: Based off boolean value print correct message regarding the sequence
**********************************************************************************/
void PDA::printResult(bool result)
{
  // print correct message regarding boolean

  if(result == true)
    {
      cout << "   ** Correct Sequence **" << endl << endl;
    }
  
  if(result == false)
    {
      cout << "   ** Sequence is syntactically incorrect **" << endl << endl;
    }
}
