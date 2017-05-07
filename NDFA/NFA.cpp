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

File Name: NFA.cpp
Description of File: Create the machine, implement core functions required to determine state, and process symbol, simulating the FA
***************************************************************************************************************************/

#include "NFA.h" //Using the NFA class created, comes with all required libraries as well

int NFA::state = 1; //Initalize static member variable at top, assuming we start at state 1 when transition

//Default constructor message nothing to be initalized or allocated
NFA::NFA()
{
  cout << "Constructor called" << endl;
}

//Default destructor message nothing to be de-allocated or freed.
NFA::~NFA()
{
  cout << endl << "Destructor called" << endl;
}

//client opens file safely with built in file name, user may not have own file name
void NFA::openEmailFile()
{
  //file name will always stay messagefile.txt
  inFile.open("messagefile.txt");
}

//print all msgID's that are marked as spam, will be computed through process symbol function
//function called at end of processing symbols, so user can see table at end of program 
void NFA:: printFinalEmailTableFormat()
{
  cout << endl;//aesthetic purposes

  /*********************************************
  sort the vector, and erase all duplicates of msgID's.
  This is neccessary due to the way I push back the msgID's in process symbol function
  **********************************************/
  sort(spam.begin(), spam.end());
  spam.erase( unique( spam.begin(),spam.end() ),spam.end());
  sort(spam.begin(), spam.end());

  
  /********************************************
  Printing spam email msgID's in table format
  ********************************************/
  cout << endl << endl << "****** SPAM ******" << endl;
  for(int i = 0; i<spam.size(); i++)
    {
      cout <<"msg" << spam[i] << endl;
    }
  cout << "****** SPAM ******" << endl;
}

//used for universal state at any given moment of machine
//used throughout to print out current state transitions based off positon of machine and symbol
void NFA:: printCurrentState(int stateCurrent)
{
  cout << "q" << stateCurrent << endl;
}

//used to reset the state to 1, when new email is read
void NFA:: resetStateForNewEmail()
{
  //1 represents the beginning of a new email and automata
  this->state = 1;
}

//used to increment the state based on certain scenario of symbol being read
void NFA:: incrementState()
{
  //member variable incremented (static member variable)
  this->state++;
}

//storing all emails/file being read into a vector of characters
//need to be stored in character since we are processing ONE symbol at a time
void NFA:: readFile(vector<char>& file)
{
  //one symbol being read and pushed back
  char symbolRead;

  //will keep pushing until reaching the end of messagefile.txt
  while(inFile.good())
    {
      //get function allows to read \n and spaces ' ', in order to process them as well
      inFile.get(symbolRead);
      file.push_back(symbolRead);
    }
}

//used for testing & prints out all msgID's found in email
//wanted to see if it was storing all msgID's found in the email
//Not used for program purposes, but for debugging purposes
void NFA:: printAllMessageID()
{
  for(int i = 0; i<msgID.size(); i++)
    {
      cout << msgID[i] << " ";
    }
}

//passing in file through vector of characters
//used to process one symbol/character at a time and call various functions to determine state/print state

void NFA:: processSymbol(vector<char> file)
{
  string id;//used to append numbers after msgID
  int total = 0;//used to determine which email it is reading, and to store correct msgID as spam
  bool sameEmail;//checked to see if you are currently on the same email or new email has been read
  static bool bodyReached = false;//checking if the body of email has been reached when \n \n has been read
  bool afterMessageID;//checking if you have reached the msg part inside <DOCID> msg and reads everything after it to store #'s
  bool reachedSubject;// used for checking when the subject in the email has been reached
  bool content;//used for the content inside the subject 
  int returnPoint;//when \n \n is reached and the FA starts here again when a wrong symbol is read other than " ' ' w f

  //used for state transition return points for various words accepted in language
  int accessState = 0;
  int softwareState = 0;
  int vacationState = 0;
  int trialState = 0;

  //start the processing of characters.symbols
  for(int i = 0; i<file.size(); i++)
    {
      //state has to be at least 15 in order to come in here, since msg can occur at <DOCID> 
      if(file[i] == 'm' && file[i+1] == 's' && file[i+2] == 'g' && state>=15)
        {
	  //increment 3 times for the m s g
          //_________________________________________
          //For the m in msg
          printCurrentState(state);
          incrementState();
          //_________________________________________
          //for the s in msg
	  printCurrentState(state);
	  incrementState();
          //_________________________________________
          //for the g in msg
          printCurrentState(state);
          incrementState();
          //_________________________________________

	  //for the number state continuous just recursive to itself but increment once
	  printCurrentState(state);
	  incrementState();
	  //counter used to read everything after g and until space is read
	  //meaning all #'s after g which is the msgID.
          int counter = 3;
          while(file[i+counter] != ' ')
            {
	      //recursively going back to itself
              //for the id after msg
              printCurrentState(state);
              //______________________________________________
	      
	      //appending the #'s read after g and storing it to msgID 
              id = id + file[i+counter];
              counter++;
            }
          msgID.push_back(id);
          id = ""; //reseting for new msg when read
          sameEmail = true;//showing that you are still in the same email
          afterMessageID = true;//showing messageID has been read and can ready to transition
        }

      /**************************************************************
      proccessing the xml beginning parts of <DOC> and so on until reaching msg.
      transitioning states by one and printing out each time
      must check for state becuse, you don't want to transition when reading these symbols anywhere else in email only at beginning
      ***************************************************************/
      //very first symbol in email must be a < for the <DOC>
      if(file[i] == '<' && state == 1)
        {
          printCurrentState(state);
          incrementState();
        }
      //transitioning from the < to D depending on the state
      if(file[i] == 'D' && state == 2)
        {
          printCurrentState(state);
          incrementState();
        }
      //transition from D to O depending on state
      if(file[i] == 'O' && state == 3)
        {
          printCurrentState(state);
          incrementState();
        }
      //transition from O to C depending on the state
      if(file[i] == 'C' && state == 4)
        {
	  printCurrentState(state);
          incrementState();
        }
      //transition from C to > depending on the state
      if(file[i] == '>' && state == 5)
        {
	  printCurrentState(state);
          incrementState();
        }
      //transition from > to new line depending on the state
      if(state == 6) //new line between doc and docid
        {
	  printCurrentState(state);
          incrementState();
        }
      //transition from new line to < beginning of the DOCID
      if(file[i] == '<' && state == 7)
        {
	  printCurrentState(state);
          incrementState();
        }
      //transition from the < to D depending on the state
      if(file[i] == 'D' && state == 8)
        {
          printCurrentState(state);
          incrementState();
        }

      //transition from the < to O depending on the state
      if(file[i] == 'O' && state == 9)
        {
          printCurrentState(state);         
	  incrementState();
        }

      //transition from the O to C depending on the state
      if(file[i] == 'C' && state == 10)
        {
          printCurrentState(state);
          incrementState();
        }
      
      //transition from the C to I depending on the state
      if(file[i] == 'I' && state == 11)
        {
          printCurrentState(state);
          incrementState();
        }

      //transition from the I to D depending on the state
      if(file[i] == 'D' && state == 12)
        {
          printCurrentState(state);
          incrementState();
        }

      //transition from the D to > depending on the state
      if(file[i] == '>' && state == 13)
        {
          printCurrentState(state);
	  incrementState();
        }
      //transition from the > to space meaning it is starting the msg part
      //rest of states handled through functions and processing part
      if(file[i] == ' ' && state == 14)
        {
          printCurrentState(state);
          incrementState();
        }

      //At least to get to space after the msg state must be >15
      if(file[i] == ' ' && afterMessageID == true)
        {
	  //When reached #'s of msg is done there is space following showing done with processing msg
	  printCurrentState(state);
          incrementState();
          afterMessageID = false;
        }
      /*******************************************************
      processing the end of msg #'s all the way to the </DOCID> \n and incrementing that many states of each symbol/character read
      ********************************************************/

      if(file[i] == '<' && file[i+1] == '/' && file[i+2] == 'D' && file[i+3] == 'O' && file[i+4] == 'C' && file[i+5] == 'I' && file[i+6] == 'D' && file[i+7] == '>' && file[i+8] == '\n')
        {
	  //incrementing once per letter: < / D O C I D > \n
	  printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();
	  printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();
	  printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();

	  //after </DOCID> you have reached the subject
          reachedSubject = true;//indication subject has been reached
        }

      // only process things in subject now
      if(reachedSubject == true)
        {
	  //Subject is defined as reading symbols of S u b j e c t : and space following colon
          if(file[i] == 'S' && file[i+1] == 'u' && file[i+2] == 'b' && file[i+3] == 'j' && file[i+4] == 'e' && file[i+5] == 'c' && file[i+6] == 't' && file[i+7] == ':' && file[i+8] == ' ')
            {
	      //Transitioning per state when reading one of those symbols above
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      //When reaching space we know the rest is the content of the subject
              if(file[i+8] == ' ')
                {
                  printCurrentState(state);
                  incrementState();
                  content = true;//indicating the content of the subject is ready to be parsed
                }
	      
              if(content == true)
                {
                  int counter = 9;
		  //processing each symbol within the subject until new line is read
		  while(file[i+counter] != '\n')
                    {
		      printCurrentState(state);
                      counter++;
                    }
		  //new line read in subject content indicates that the body is near
                }
            }//actual subject functionality
        }//subject parsing

      //Reached body, when processing two new lines consecutively you are done with subject and now in body
      if(file[i] == '\n' && file[i+1] == '\n')
        {
	  //Increment state twice becuse these are necessary transitions to reach body parsing
          //for 1st new line for body
	  printCurrentState(state);
          incrementState();
          //___________________________________
          printCurrentState(state);
	  incrementState();
          //___________________________________

          bodyReached = true;//showing that the body is ready to process symbols
          reachedSubject = false;//no longer in the subject of same email
          content = false;//not inside subject content anymore
          returnPoint = state;//keeping track of state of machine after \n \n is read
        }
            
      //processing one symbol at a time and transition depending on state and symbol being read
      //processing everything within body this is special case if the word is the very first within the body
      // this case is for any word with quotes and f in the beginning of the body
      if(file[i-1] == '\n' && file[i] == '"' && file[i+1] == 'f' &&  bodyReached == true)
	{
	  //state transitions twice since it reads quote and f
	  printCurrentState(state);
	  incrementState();
	  printCurrentState(state);
	  incrementState();
	  //all symbols in the words share the r e e  and space following the word free
	  if(file[i+2] == 'r' && file[i+3] == 'e' && file[i+4] == 'e' && file[i+5] == ' ')
	    {
	      //must increment per every symbol read in the r e e and space
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //space is necessary because the words accepted in language for free have space after free indicating two words
	    }
	  //checking symbols of free access
	  //transition state depending on if condition met for all a c c e s s " and space or new line following the quote
	  if(file[i+6] == 'a' && file[i+7] == 'c' && file[i+8] == 'c' && file[i+9] == 'e' && file[i+10] == 's' && file[i+11] == 's' && file[i+12] == '"' && (file[i+13] == ' ' || file[i+13] == '\n') && bodyReached == true)
	    {
	      //the body is reached and we are processing symbols of a c c e s s quote and new line or space
	      state = state + 7; // where to start since multiple transitions from same node (based off FA drawing
	      //transitioning states per symbol read a c c e s s " and space or new line
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
	      incrementState();
	      accessState = state;
	      //when transitions complete print for readability and debugging purposes
	      cout << "quote free access quote found in msg" << msgID[total] << endl;
	      //when the word was found push id into spam
	      spam.push_back(msgID[total]);
	    }
	  
	  //checking symbols of s o f t w a r e quote and space or new line after
	  if(file[i+6] == 's' && file[i+7] == 'o' && file[i+8] == 'f' && file[i+9] == 't' && file[i+10] == 'w' && file[i+11] == 'a' && file[i+12] == 'r' && file[i+13] == 'e' && file[i+14] == '"' && (file[i+15] == ' ' || file[i+15] == '\n') && bodyReached == true)
            {
	      //withing body being reached these symbols can be processed and used to transition
	      state = state + 7;// must start at a diferent area
	      //transitioning from s o f t w a r e quote and space or new line
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      softwareState = state;
	      //when transitions complete print for readability and debugging purposes
	      cout << "quote free software quote found in msg" << msgID[total] << endl;
	      //when the word was found push the id into spam
	      spam.push_back(msgID[total]);
	    }  

	  //when processing the v a c a t i o n symbols in conseuctive order and the body is reached
	  if(file[i+6] == 'v' && file[i+7] == 'a' && file[i+8] == 'c' && file[i+9] == 'a' && file[i+10] == 't' && file[i+11] == 'i' && file[i+12] == 'o' && file[i+13] == 'n' && file[i+14] == '"' && (file[i+15] == ' ' || file[i+15] == '\n') && bodyReached == true)
	    {
	      // transition to a new state starting to process the symbols above
	      state = state + 9; //amount of software length
	      //transition states of v a c a t i o n quote and space or new line after
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      vacationState = state;
	      //when transitions complete print for readability and debugging purposes
	      cout << "quote free vacation quote found in msg" << msgID[total] << endl;
	      //when found push the msg id into spam
	      spam.push_back(msgID[total]);
	    }
	      
	  //when reached body and the t r i a l s and quote is ready to be processed per symbol
	  if(file[i+6] == 't' && file[i+7] == 'r' && file[i+8] == 'i' && file[i+9] == 'a' && file[i+10] == 'l' && file[i+11] == 's' && file[i+12] == '"' && (file[i+13] == ' ' || file[i+13] == '\n') && bodyReached == true)
	    {
	      //transition to a new state whre processing for t r i a l s " starts
	      state = state + 9; //amount of vacation length
	      //transition per symbol read and matched
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      trialState = state;
	      //print when transitions are complete for readability and debugging purposes
	      cout << "quote free trials quote found in msg" << msgID[total] << endl;
	      //push the msg id into spam when found
	      spam.push_back(msgID[total]);
	    }
	  
	}//beginning of body with quotes and F

      //start the processing and states when the body is reached and word begins with f and at the beginning of the body
      if(file[i-1] == '\n' && file[i] == 'f' && bodyReached == true)
	{
	  //transition per the state f reached
	  printCurrentState(state);
	  incrementState();
	  //all words transition and share the states of r e e and space following
	  if(file[i+1] == 'r' && file[i+2] == 'e' && file[i+3] == 'e' && file[i+4] == ' ')
	    {
	      //transition states based off of r e e and space per symbol
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      //space must be considered since free ' ' follows another word in order to be accepted in the language. 
	    }
	  
	  //start the the processing and states of a c c e s s and followed by previous symbols 
	  if(file[i+5] == 'a' && file[i+6] == 'c' && file[i+7] == 'c' && file[i+8] == 'e' && file[i+9] == 's' && file[i+10] == 's' && (file[i+11] == ' ' || file[i+11] == '\n') && bodyReached == true)
	    {
	      //transition per state of a c c e s s and the space or new line after
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //when transitions complete print for debugging and readability purposes
	      cout << "free access found in msg" << msgID[total] << endl;
	      //push msgID into the spam vector
	      spam.push_back(msgID[total]);
	    }
	
	  //strt the processing and states of s o f t w a r e and space or new line following
	  if(file[i+5] == 's' && file[i+6] == 'o' && file[i+7] == 'f' && file[i+8] == 't' && file[i+9] == 'w' && file[i+10] == 'a' && file[i+11] == 'r' && file[i+12] == 'e' && (file[i+13] == ' ' || file[i+13] == '\n'))
	    {
	      //transition states per symbol that is processed from the s o f t w a r e and the space or new line
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //when transitions complete print word for readability/debugging purposes
	      cout << "free software found in msg" << msgID[total] << endl;
	      //push msg id into spam vector when found
	      spam.push_back(msgID[total]);
	    }

	  //start processing and states of v a c a t i o n and space or new line followed
	  if(file[i+5] == 'v' && file[i+6] == 'a' && file[i+7] == 'c' && file[i+8] == 'a' && file[i+9] == 't' && file[i+10] == 'i' && file[i+11] == 'o' && file[i+12] == 'n' && (file[i+13] == ' ' || file[i+13] == '\n'))
	    {
	      //transition states depending on the symbols processed from v a c a t i o n and space or new line
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //when transitions complete print word for readability/debugging purposes
	      cout << "free vacation found in msg" << msgID[total] << endl;
	      //push msg id into spam vector when found
	      spam.push_back(msgID[total]);
	    }
	  
	  //start processing and states of t r i a l s and space or new line
	  if(file[i+5] == 't' && file[i+6] == 'r' && file[i+7] == 'i' && file[i+8] == 'a' && file[i+9] == 'l' && file[i+10] == 's' && (file[i+11] == ' ' || file[i+11] == '\n'))
	    {
	      //transition states depending on the symbols being read in from t r i a l s and space or new line 
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //when transitions complete print for readbility and debugging purposes
	      cout << "free trials found in msg" << msgID[total] << endl;
	      //push msg id in to the spam vector when found
	      spam.push_back(msgID[total]);
	    }		
	}//For the very beginning of body for F   
     
      //within the body of the email if it starts with quote and followed by f 
      if(file[i-1] == ' ' && file[i] == '"' && file[i+1] == 'f' && bodyReached == true)
        {
	  //transition two states because of quote and f being processed
          printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();

	  //sharing same symbols of r e e and space followed
          if(file[i+2] == 'r' && file[i+3] == 'e' && file[i+4] == 'e' && file[i+5] == ' ')
            {
	      //transition states r e e and space 
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
            }
	  //if any other symbol is read throughout the process then it will return the state of \n \n
	  else
	    {
	      state = returnPoint;
	      printCurrentState(state);
	    }

	  //process symbols of a c c e s s and quote following the previous symbols 
          if(file[i+6] == 'a' && file[i+7] == 'c' && file[i+8] == 'c' && file[i+9] == 'e' && file[i+10] == 's' && file[i+11] == 's' && file[i+12] == '"' && (file[i+13] == ' ' || file[i+13] == '\n') && bodyReached == true)
            {
	      //start the access state, determined by the FA
	      state = returnPoint + 7;
	      //transition per symbol in the state
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      accessState = state;
	      
	      //when transition complete print for readability/debugging purposes
              cout << " quote free access quote found in msg " << msgID[total] << endl;
              //push back msg id into spam
	      spam.push_back(msgID[total]);
            }

	  //if any other symbol is read through the process then it wil reutrn the state of \n \n
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }

	  //proces symbols of s o f t w a r e and quote followed by space or new line
	  if(file[i+6] == 's' && file[i+7] == 'o' && file[i+8] == 'f' && file[i+9] == 't' && file[i+10] == 'w' && file[i+11] == 'a' && file[i+12] == 'r' && file[i+13] == 'e' && file[i+14] == '"' && (file[i+15] == ' ' || file[i+15] == '\n') && bodyReached == true)
            {
	      //transition to the state that correlates to the software processing in the FA
	      state = returnPoint + 14;
	      //transition per symbol in the states
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
	      softwareState = state;
	      //when found after transitions complete print for debugging and readability purposes
              cout << "quote free software quote found in msg " << msgID[total] << endl;
	      //push back the msg id into the spam vector
              spam.push_back(msgID[total]);
            }
	  //if anything else is processed then return to the state of \n \n and begin processing again
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }

	  //start processing of the v a c a t i o n followed by quote and space or new line
          if(file[i+6] == 'v' && file[i+7] == 'a' && file[i+8] == 'c' && file[i+9] == 'a' && file[i+10] == 't' && file[i+11] == 'i' && file[i+12] == 'o' && file[i+13] == 'n' && file[i+14] == '"' && (file[i+15] == ' ' || file[i+15] == '\n') && bodyReached == true)
            {
	      //transition to the state that begins processing the v a c a t i o n quote 
	      state = returnPoint + 23;
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();

	      vacationState = state;
	      //when found print for debugging and readability purposes
              cout << "quote free vacation quote found in msg " << msgID[total] << endl;
              //push msg id into spam
	      spam.push_back(msgID[total]);
            }

	  //if anything else is read than return to the \n \n state
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }
	  
	  //begin processing for the t r i a l s and quote followed by space or new line
	  if(file[i+6] == 't' && file[i+7] == 'r' && file[i+8] == 'i' && file[i+9] == 'a' && file[i+10] == 'l' && file[i+11] == 's' && file[i+12] == '"' && (file[i+13] == ' ' || file[i+13] == '\n') && bodyReached == true)
            {
	      //transition to the state that will begin processing this on the FA
	      state = returnPoint + 32;
	      //transition per symbol depending on the symbol processed
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();

	      trialState = state;
	      //print for readability and debugging purposes
              cout << "quote free trials quote found in msg " << msgID[total] << endl;
              //push msg id into vector 
	      spam.push_back(msgID[total]);
            }
	  
	  //if anything else is processed than return to the \n \n state 
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }

        }//End of F with quotes

      //start processing the space followed by f scenarios and body is being read
      if(file[i] == ' ' && file[i+1] == 'f' && bodyReached == true)
        {
	  //transition two states because of the space and f
          //_________________________________________
	  printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();
          //_________________________________________

	  //all symbols correspond to the r e e followed by space
          if(file[i+2] == 'r' && file[i+3] == 'e' && file[i+4] == 'e' && file[i+5] == ' ')
            {
	      //transition per symbol read in the r e e and space
              //_________________________________________
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              //_________________________________________
            }
	  
	  //if anything else is processed than return to the \n \n and begin processing again
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }
	  
	  //start processing the a c c e s s and space or new line 
	  if(file[i+6] == 'a' && file[i+7] == 'c' && file[i+8] == 'c' && file[i+9] == 'e' && file[i+10] == 's' && file[i+11] == 's' && file[i+12] == ' ' || file[i+12] == '\n' && bodyReached == true)
            {
              //____________________________________________
	      //transition to the state on FA that processes these symbols
	      state = returnPoint + 6;
	     
	      //transition per symbol read and processed
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              //___________________________________________
	      accessState = state;
	      
	      //print when transition are complete for readability and debugging purposes
              cout << "free access found in : msg" << msgID[total] << endl;
	      //push back the msgid found 
              spam.push_back(msgID[total]);
            }
	  
	  //start processing the symbols of s o f t w a r e and space or new line followed
	  if(file[i+6] == 's' && file[i+7] == 'o' && file[i+8] == 'f' && file[i+9] == 't' && file[i+10] == 'w' && file[i+11] == 'a' && file[i+12] == 'r' && file[i+13] == 'e' && file[i+14] == ' ' || file[i+14] == '\n' && bodyReached == true)
	    {
	      //_________________________________________
	      //transition to state that starts processing the corresponding symbols
	      state = returnPoint + 13;
	      //transition per symbol read and processed
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      //_________________________________________
	      softwareState = state;
	      //print when transitions are complete for readability and debugging purposes
	      cout << "free software found in: msg" << msgID[total] << endl;
	      //push msg id back into spam vector
	      spam.push_back(msgID[total]);
	    }

	  //if anything else is processed than return to the \n \n point
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }

	  //start processing the v a c a t i o n and space or new line followed
	  if(file[i+6] == 'v' && file[i+7] == 'a' && file[i+8] == 'c' && file[i+9] == 'a' && file[i+10] == 't' && file[i+11] == 'i' && file[i+12] == 'o' && file[i+13] == 'n' && file[i+14] == ' ' || file[i+14] == '\n' && bodyReached == true)
	    {
	      //___________________________________________
	      //transition to state on FA that processes the symbols
	      state = returnPoint + 22;
	      //transition state dependin on symbol being processed
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      //__________________________________________
	      vacationState = state;
	      //print when transitions are complete for readability/debugging purposes
	      cout << "free vacation found in: msg" << msgID[total] << endl;
	      //push msg id into spam vector
	      spam.push_back(msgID[total]);
	    }
	  //if anything else is processed, than return to the state of \n \ n
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }

	  //start processing the t r i a l s followed by space or new line
	  if(file[i+6] == 't' && file[i+7] == 'r' && file[i+8] == 'i' && file[i+9] == 'a' && file[i+10] == 'l' && file[i+11] == 's' && file[i+12] == ' ' || file[i+12] == '\n' && bodyReached == true)
	    {
	      //transition to state that processes the corresponding symbols
	      state = returnPoint + 31;
	      //_____________________________________________
	      //transition per symbol read
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      //____________________________________________

	      trialState = state;
	      //print when transitions are complete for readability and debugging purposes
	      cout << "free trials found in: msg" << msgID[total] << endl;
	      //push msg id into vector
	      spam.push_back(msgID[total]);
	    }
	  //if anything else is read than transition to state of \n \n 
	  else
            {
              state = returnPoint;
	      printCurrentState(state);
            }

        }//Close outter with f
  

      //start processing the w languages if very beginning of body
      if(file[i-1] == '\n' && file[i] == '"' && file[i+1] == 'w' && bodyReached == true)
	{
	  //transition two states after processing the quote and w
	  printCurrentState(state);
	  incrementState();
	  printCurrentState(state);
	  incrementState();

	  //followed by the i then process the state and transition
	  if(file[i+2] == 'i')
	    {
	      printCurrentState(state);
	      incrementState();
	    }
	  //process the corresponding symbols of n followed by quote and space or new line
	  if(file[i+3] == 'n' && file[i+4] == '"' && (file[i+5] == ' ' || file[i+5] == '\n'))
	    {
	      //transition per symbol processed 
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	  
	      //when transitions complete print for readaility and debugging purposes
	      cout << "quote win quote found in msg" << msgID[total] << endl;
	      //push msg id back into vector
	      spam.push_back(msgID[total]);
	    }
	  
	  //process the corresponding symbols of n n e r quote followed by space or new line
	  if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'e' && file[i+6] == 'r' && file[i+7] == '"' && (file[i+8] == ' ' || file[i+8] == '\n'))
	    {
	      //transition per symbol processed
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	    
	      //when transitions complete print readability and debugging purposes
	      cout << "quote winner quote found in msg" << msgID[total] << endl;
	      //push msg id back into vector
	      spam.push_back(msgID[total]);
	    }
	  
	  //process corresponding symbols of n n e r s quote followed by space or new line
	  if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'e' && file[i+6] == 'r' && file[i+7] == 's' && file[i+8] == '"' && (file[i+9] == ' ' || file[i+9] == '\n'))
	    {
	      //transition per symbol processed
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //if transitions complete print for readability and debugging purposes
	      cout << "quote winners quote found in msg" << msgID[total] << endl;
	      //push msg id back into vector
	      spam.push_back(msgID[total]);
	      }
	  
	  //start processing the n n i n g s quote followed by space or new line
	  if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'i' && file[i+6] == 'n' && file[i+7] == 'g' && file[i+8] == 's' && file[i+9] == '"' && (file[i+10] == ' ' || file[i+10] == '\n'))
	    {
	      //transition per symbol processed
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      
	      //when transitions complete print word for readability and debugging purposes
	      cout << "quote winnings quote found in msg" << msgID[total] << endl;
	      //push msg id into vector
	      spam.push_back(msgID[total]);
	    }
	}//beginning of body with quote and w  
      
      
      //Beginning of body with start of w and body has been reached
      if(file[i-1] == '\n' && file[i] == 'w' && bodyReached == true)
	{
	  //transition state once from the w being processed
	  printCurrentState(state);
	  incrementState();
	  
	  //process the symbol i
	  if(file[i+1] == 'i')
	    {
	      //transition state 
	      printCurrentState(state);
	      incrementState();
	    }
	  
	  //process the w and space for the acceptance of win
	  if(file[i+2] == 'n' && (file[i+3] == ' ' || file[i+3] == '\n'))
	    {
	      //transition twice for the n and space or new line being processed
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
	      //after transition print for readability/debugging
	      cout << "win found in msg" << msgID[total] << endl;
	      //push msg id into vector
	      spam.push_back(msgID[total]);
	    }	  
	  
	  //process the n n e r followed by space or new line
	  if(file[i+2] == 'n' && file[i+3] == 'n' && file[i+4] == 'e' && file[i+5] == 'r' && (file[i+6] == ' ' || file[i+6] == '\n'))
	    {
	      //transition per symbol processed
	      printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //after all transition print for readability/debugging purposes
	      cout << "winner found in msg" << msgID[total] << endl;
	      //push msg id into vector
	      spam.push_back(msgID[total]);
	    }
	  //process the n n e r s and space or new line 
	  if(file[i+2] == 'n' && file[i+3] == 'n' && file[i+4] == 'e' && file[i+5] == 'r' && file[i+6] == 's' && (file[i+7] == ' ' || file[i+7] == '\n'))
	    {
	      //transition per symbol processed
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      
	      //after all transitions print for readability/debugging purposes
	      cout << "winners found in msg" << msgID[total] << endl;
	      //push msg id into vector
	      spam.push_back(msgID[total]);
	    }

	  //process the n n i n g s followed by space or new line
	  if(file[i+2] == 'n' && file[i+3] == 'n' && file[i+4] == 'i' && file[i+5] == 'n' && file[i+6] == 'g' && file[i+7] == 's' && (file[i+8] == ' ' || file[i+8] == '\n'))
	    {
	      //transition per symbol processed
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //after transition print for readability/debugging purposes
	      cout << "winnings found in msg" << msgID[total] << endl;
	      //push msg id into vector
	      spam.push_back(msgID[total]);
	    }
	}//for beginning of w no quote

      //start processing w with quote and space before the beginning of word and when body is reached          
      if(file[i-1] == ' ' && file[i] == '"' && file[i+1] == 'w' && bodyReached == true)
        {
	  //transition to state on FA that processes these symbols
	  state = state + 38; //38 states added because of ending of word free trials, now start w's
	  //transition per symbol processed
	  printCurrentState(state);
	  incrementState();
	  printCurrentState(state);
	  incrementState();
          printCurrentState(state);
	  incrementState();

	  //process the i 
          if(file[i+2] == 'i' && bodyReached == true)
            {
	      //transition per symbol
              printCurrentState(state);
              incrementState();
            }
	  //if anything else is read return to the \n \n state
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }
	  
	  //process the n quote and first acceptance 
          if(file[i+3] == 'n' && file[i+4] == '"' && file[i+5] == ' ' || file[i+5] == '\n' && bodyReached == true)
            {
	      //transition to state on FA that processes the "win"
	      state = state + 41;
	      //transition per symbol processed
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      //after all transition processed print for readabilit/debugging
              cout << "quote win quote found in msg " << msgID[total] << endl;
	      //push msg id back into vector
              spam.push_back(msgID[total]);
            }
	  //if anything else is read return to the \n \n state
	  else
            {
              state = returnPoint;
	      printCurrentState(state);
            }

	  //begin processing the following symbols of n n e r quote followed by space or new line
          if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'e' && file[i+6] == 'r' && file[i+7] == '"' && file[i+8] == ' ' || file[i+8] == '\n' && bodyReached == true)
            {
	      //transition to the state on FA that processes the corresponding symbols
	      state = state + 44;
	      //transition per symbol processed
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      //after all transition made print for readability/debugging purposes
              cout << "quote winner quote found in msg " << msgID[total] << endl;
	      //push id into vector
              spam.push_back(msgID[total]);
            }
	  //if anything else is read than return to the \n \n state
	  else
            {
              state = returnPoint;
	      printCurrentState(state);
            }

	  //begin processing the n n e r s quote followed by space or new line 
	  if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'e' && file[i+6] == 'r' && file[i+7] == 's' && file[i+8] == '"' && file[i+9] == ' ' || file[i+9] == '\n' && bodyReached == true)
            {
	      //transition to state on FA that processes corresponding states
	      state = state + 50;
	      //transition per symbol being processed
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
	      incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      //after all transitions made print for readability/debugging purposes
              cout << "quote winners quote found in msg " << msgID[total] << endl;
	      //push msg id into vector
              spam.push_back(msgID[total]);
            }
	  //if anything else is processed than return to the \n \n state
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }
	  
	  //begin processing the n n i n g s quote followed by space or new line
          if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'i' && file[i+6] == 'n' && file[i+7] == 'g' && file[i+8] == 's' && file[i+9] == '"' && file[i+10] == ' ' || file[i+10] == '\n' && bodyReached == true)
            {
	      //transition to state on FA that processes corresponding symbols
	      state = state + 57;
	      //transition per symbol being processed
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
	      incrementState();
              printCurrentState(state);
	      incrementState();
	      //after all transition print for readability/debugging purposes
              cout << "quote winnings quote found in msg " << msgID[total] << endl;
	      //push msg id into vector
              spam.push_back(msgID[total]);
            }

	  //if anything else is procesed return to the \n \n state
	  else
            {
              state = returnPoint;
	      printCurrentState(state);
            }

        }//all W with quotes in language

      //FOR ALL W's in language in the body followed by space before
      if(file[i] == ' ' && file[i+1] == 'w' && bodyReached == true)
        {
	  //transition to state on FA that processes corresponding symbols
	  state = 38;
	  //transition per symbol processed
          printCurrentState(state);
          incrementState();
          printCurrentState(state);
	  incrementState();

	  //transition for i symbol followed previously by the symbols read
          if(file[i+2] == 'i')
            {
	      //transition per symbol processed
              printCurrentState(state);
              incrementState();
            }
	  //if anything else is processed return to \n \n state
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }
	  
	  //begin processing n followed by space or new line when body is reched
          if(file[i+3] == 'n' && file[i+4] == ' ' || file[i+4] == '\n' && bodyReached == true)
            {
	      //transition to state on FA that processes corresponding symbols
	      state = state + 41;
	      //transition per symbol processed
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
	      //when transitions complete print for readability/debugging purposes
              cout << " win found in: msg"<< msgID[total] << endl;
	      //push msg id into vector
              spam.push_back(msgID[total]);
            }
	  //if anything else is processed return to the \n \n state
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }
	  
	  //begin processing the n n e r followed by space or new line
	  if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'e' && file[i+6] == 'r' && file[i+7] == ' ' || file[i+7] == '\n' && bodyReached == true)
            {
	      //transition to state on FA that processes corresponding symbols
	      state = state + 44;
	      //transition per symbol processed
	      printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      
	      //after transitions complete print for readability/debugging purposes
              cout << "winner found in: msg" << msgID[total] << endl;
	      //push msg id into vector
              spam.push_back(msgID[total]);
            }
	  //if anything else is processed return to the \n \n state
	  else
            {
              state = returnPoint;
	      printCurrentState(state);
            }

	  //begin processing the n n e r s followed by space or new line
          if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'e' && file[i+6] == 'r' && file[i+7] == 's' && file[i+8] == ' ' || file[i+8] == '\n' && bodyReached == true)
            {
	      //transition to state on the FA that processes corresponding symbols
	      state = state + 50;
	      //transition per symbol processed
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
	      printCurrentState(state);
              incrementState();

	      //after all transition made print for readability/debugging purposes
              cout << " winners found in: msg" << msgID[total] << endl;
	      //push msg id into vector
              spam.push_back(msgID[total]);
            }
	  
	  //if anything else is processed return to the \n \n state
	  else
            {
              state = returnPoint;
              printCurrentState(state);
            }

	  //begin processing the n n i n g s followed by space or new line
          if(file[i+3] == 'n' && file[i+4] == 'n' && file[i+5] == 'i' && file[i+6] == 'n' && file[i+7] == 'g' && file[i+8] == 's' && file[i+9] == ' ' || file[i+9] == '\n' && bodyReached == true)
            {
	      //transition to state on the FA that processes correspinding symbols
	      state = state + 57;
              //_________________________________________
	      //transition every symbol being processed
	      printCurrentState(state);
	      incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
              incrementState();
              printCurrentState(state);
	      incrementState();
              printCurrentState(state);
              incrementState();
	      printCurrentState(state);
              incrementState();
	      printCurrentState(state);
	      incrementState();
              //_______________________________________
	      //after all transitions made print for readability/debugging purposes
              cout << "winnings found in: msg" << msgID[total] << endl;
	      //push msg id into vector
              spam.push_back(msgID[total]);
            }
 	  
	  //if anything else is processed return to the \n \n state
	  else
	    {
	      state = returnPoint;
	      printCurrentState(state);
	    }
        }//end of w with space processing of symbols

      //knowing the ending of the email process corresponding symbols
      if(file[i] == '<' && file[i+1] == '/' && file[i+2] == 'D' && file[i+3] == 'O' && file[i+4] == 'C' && file[i+5] == '>')
        {
	  //transition to state on FA that processes corresponding symbols
	  state = state + 63;
	  //transition per symbol processed
	  printCurrentState(state);
	  incrementState();
	  printCurrentState(state);
	  incrementState();
	  printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();
	  printCurrentState(state);
          incrementState();
          printCurrentState(state);
          incrementState();

	  cout << "______________________________________________________________" << endl; 
          //reset sameEmail because now reading next email
	  sameEmail = false;
	  //total represents the email number
          total++;
	  //body reached is now false you are done processing symbols from body
          bodyReached = false;
	  //reset state back to beginning of FA and re-process symbols for new email
          resetStateForNewEmail();
        }
    }//End of processing file/emails

}//end of function implementation
