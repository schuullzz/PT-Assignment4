//Author: Timothy Schultz
//CS 4280
//Project 4

#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>
#include "scanner.h"
#include "token.h"

extern std::vector<tokenType> tokenVec;

//Function that determines what error message to display.
int errorScanner(int flag , int numberLine)
{
	//Shows correct error message.
	if(flag == 1)
	{
		//std::cout << "\n";
		std::cout << "Incorrect syntax for identifier." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
		return 1;
	}
	else if(flag == 2)
	{
		//std::cout << "\n";
		std::cout << "Incorrect character input." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
		return 1;
	}
	else if(flag == 3)
	{
		//std::cout << "\n";
		std::cout << "Incorrect number of digits allowed." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

//Driver function for scanner.
int FADriver(std::string holder, int lineNumber)
{
	//Initiates state in FSA table.
	stateT state = S1;
	//Creates the next state in the FSA table. 
	stateT nextState;
	//Creates token object to contain token info.
	tokenType token;
	//Used to increment through loops.
	int x = 0;
	//Initiates column to -1.
	int column = -1;
	//Contains the current index within string.
	int index = 0;
	//String that is built for tokens.
	std::string s = "";
	//Contains the length of the string passed to function.
	int inputLength = (int)holder.length();
	//Contains the size of the char array.
	int arrLen = sizeof(charColumn)/sizeof(charColumn[0]);
	//Contains the size of the string array.
	int arrLen2 = sizeof(keyWords)/sizeof(keyWords[0]);
	//Flag flipped if keyword is detected.
	int keyWordFlag = 0;
	//Flag flipped if number is larger than 8.
	int digitCounter = 0;
	//adds a space to the end of the sting inputed for scanner.
	holder += " ";
	//Flag
	int errorFlag;	

	//Returns EOF_tk and information
	if(holder == "EOF ")
	{
		token.id = S27;
		token.symbol = "EOF";
		token.tokenInstance = tokeNames[S27];
		token.lineNumber = lineNumber;
		//printToken(token);
		tokenVec.push_back(token);
		return 0;
	}

	//While loop that breaks up into tokens and returns when the length of the
	//string has been met or error has occured.
	while(1)
	{
		//Flag is reset if last token was a keyword.
		keyWordFlag = 0;
		//Column is always set to -1 for integer or identifier.
		column = -1;

		//Loops through to see if symbol is detected in char array.
		for(x = 0; x < arrLen; x++)
		{
			if(charColumn[x] == holder[index])
			{
				column = x;
			}
		}

		//Determines if the token is an integer, identifier, an error has occured,
		//or the character was found in the column.
		if(column == -1 && isdigit(holder[index]))
		{
			//Determined to be an integer.
			column = 20;
			nextState = table[state][column];
			digitCounter++;
			
			//Checks to make sure 8 digits has not be exceeded. 
			if(digitCounter > 8)
			{
				errorFlag = errorScanner(3, lineNumber);
				return errorFlag;
			}
	
		}
		else if(column == -1 && (holder[index] == '_' || islower(holder[index])))
		{
			//Determined to be a identifier because starts with lower case letter
			//or an underscore.
			column = 19;
			nextState = table[state][column];	
		}
		else if(column == -1 && (isalpha(holder[index]) || isdigit(holder[index])))
		{
			//Identifier contians a alphabetic or number char.
			column = 19;
			nextState = table[state][column];	
		}
		else if(column == -1)
		{
			//Does not follow rules for characters error has occured.
			nextState = ERROR;
		}
		else
		{
			nextState = table[state][column];
		}
	
		//character error has occured.
		if(nextState == ERROR)
		{
			errorFlag = errorScanner(2, lineNumber);
			return errorFlag;
		}

		//Token has finallized.
		if(nextState == FINAL)
		{
			digitCounter = 0;

			//identified as a identifier.
			if(state == S24)
			{

				//verifies that the rules of an identifier have been followed.
				if(s[0] != '_' && isupper(s[0]))
				{
					errorFlag = errorScanner(1, lineNumber);
					return errorFlag;
				}
				
				for(x = 1; x < (int)s.length(); x++)
				{
					if(!isalpha(s[x]) && !isdigit(s[x]))
					{
						errorFlag = errorScanner(1, lineNumber);
						return errorFlag;
					} 
				}			
	
				//Checks to see if identifier is a keyword.
				for(x = 0; x < arrLen2; x++)
				{
					if(s == keyWords[x])
					{
						//stores information and passes it to printToken function to 
						//be displayed.
						token.id = S26;
						token.symbol = s;
						token.tokenInstance = tokeNames[S26];
						token.lineNumber = lineNumber;
						//printToken(token);
						tokenVec.push_back(token);
						state = S1;
						s = "";

						if(holder[index] == ' ')
						{
							index++;
						}

						//Flips flag for keyword.
						keyWordFlag = 1;
						break;
					}
				}
					
				//Verifies that keyword was found
				if(keyWordFlag == 0)
				{
					//Stores information and passes it to printToken function to be displayed.
					token.id = state;
					token.symbol = s;
					token.tokenInstance = tokeNames[state];
					token.lineNumber = lineNumber;
					//printToken(token);
					tokenVec.push_back(token);
					state = S1;
					s = "";

					if(holder[index] == ' ')
					{
						index++;
					}
				}
				
			}
			else
			{
				//Stores information for character token and passes it to printToken function to
				//be displayed.
				token.id = state;
				token.symbol = s;
				token.tokenInstance = tokeNames[state];
				token.lineNumber = lineNumber;
				//printToken(token);
				tokenVec.push_back(token);
				state = S1;
				s = "";

				if(holder[index] == ' ')
				{
					index++;
				}
			}	
			
		}
		else
		{
			//Continues to build the string in final state is reached.
			state = nextState;
			if(holder[index] != ' ')
			{
				s += holder[index];
			}
			index++;
		}

		//Breaks out of loop if index is greater than the input string length.
		if(index > inputLength)
		{
			break;
		}
		
	}
	
	return 0;

}
