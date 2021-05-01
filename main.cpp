//Author: Timothy Schultz
//CS 4280
//Project 4

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "scanner.h"
#include "parser.h"
#include "generator.h"
#include "node.h"

//prototypes
static void usage(std::string);
static void readFile(std::string);
static void readInput();

//Static global variable
static int flagNf;
static int flagF;
std::string fileBegin;
std::string fileDelete;

//Global vector
std::vector<tokenType> tokenVec;

int main(int argc, char* argv[])
{
	//contains switch value. 
	int opt;
	//String containing file name
	std::string fileName = argv[0];

	//*******************************************
	
	//Getopts to parse h.
	while((opt = getopt(argc, argv, "h")) != -1)
	{
		switch(opt)
		{
			case 'h':
				usage(fileName);
				return 0;
			case '?':
				usage(fileName);
				return 0;	
		}
	}

	//*******************************************

	//Determines the amount of arguments passed
	if(argc == 1)
	{
		if(isatty(STDIN_FILENO))
		{
			usage(fileName);
		}
		else
		{
			flagNf = 1;
			readInput();
		}	
	}
	else if(argc == 2)
	{
		//Flag for file set to one.
		flagF = 1;

		std:: string openFileName = ""; 
		openFileName += argv[1];
		fileBegin = openFileName.substr(0, openFileName.find("."));
		fileBegin += ".asm";
		fileDelete = fileBegin;
		readFile(openFileName);
	}
	else
	{
		usage(fileName);
		return 0;	
	}

	return 0;
} 

//Displays to the user how program works. [-h]
static void usage(std::string file)
{
	std::cout << "Usage: " << file << " [file]" << std::endl;
	std::cout << "Usage: " << file << " < [file]" << std::endl;
}

//When file is passed as argument this function is called
static void readFile(std::string openFile)
{
	//Creates file object with file name.
	std::ifstream file(openFile.c_str());

	if(file == NULL)
	{
		std::cout << "Unable to open file." << std::endl;
		exit(1);
	}

	//Contains string from file.
	std::string inputHolder = "";
	//String from file with out comments.
	std::string passedString = "";
	//Contains the index of the string.
	int index;
	//Contains the line number
	int lineNumber = 0;
	//Flips if comment has been made. Checks error.
	int commentFlag = 0;
	//Error Flag
	int errorFlag = 0;

	//interates through the file if a string is present.
	while(std::getline(file, inputHolder))
	{
		//Flips to zero everytime there is a new line retreived.
		index = 0;	
		
		//While loop that breaks when the length of string is matched.
		while(1)
		{
			//Only adds to the string if no comments, $ symbol, and index does not equal the length
			//of the string.
			if(commentFlag == 0 && inputHolder[index] != '$' && index != (int)inputHolder.length())
			{
				passedString += inputHolder[index];
			}

			//Breaks the loop if index is last in the string.
			//Checks if comment exists and implemented correctly.
			//Otherwise index is increased.
			if(index == (int)inputHolder.length())
			{
				errorFlag = FADriver(passedString, lineNumber);
			
				//Stops program if error detected.		
				if(errorFlag == 1)
				{
					return;
				}		

				lineNumber++;
				passedString = "";
				inputHolder = "";
				break;
			}
			else if(inputHolder[index] == '$')
			{
				index++;

				if(inputHolder[index] == '$')
				{
					commentFlag += 1;		
					index++;	
			
					if(commentFlag == 2)
					{
						commentFlag = 0;
					}
				}
				else
				{
					std::cout << "Error has occured with comment syntax." << std::endl;
					return;
				}
			}
			else
			{
				index++;
			}
				
		}
	}

	file.close();

	//Issued a end of token since file ended.
	errorFlag = FADriver("EOF", lineNumber);
	
	//Stops program if error detected.		
	if(errorFlag == 1)
	{
		return;
	}
	
	node *tree = parser();

	std::ofstream outFile(fileBegin.c_str());

	if(outFile == NULL)
	{
		std::cout << "Unable to create/write to file." << std::endl;
		exit(1);
	}

	recGen(tree, outFile);
	
	outFile.close();
}

//Function is called to read from keyboard.
static void readInput()
{
	std::string keyboardFile = "kb.asm";
	fileDelete = keyboardFile;

	//Contains string from file.
	std::string inputHolder = "";
	//String from file with out comments.
	std::string passedString = "";
	//Contains the index of the string.
	int index = 0;
	//Contains the line number
	int lineNumber = 0;
	//Flips if comment has been made. Checks error.
	int commentFlag = 0;
	//Error Flag
	int errorFlag = 0;

	while(getline(std::cin, inputHolder))
	{
		//Flips to zero everytime there is a new line retreived.
		index = 0;

		while(1)
		{
			//Only adds to the string if no comments, $ symbol, and index does not equal the length
			//of the string.
			if(commentFlag == 0 && inputHolder[index] != '$' && index != (int)inputHolder.length())
			{
				passedString += inputHolder[index];
			}

			//Breaks the loop if index is last in the string.
			//Checks if comment exists and implemented correctly.
			//Otherwise index is increased.
			if(index == (int)inputHolder.length())
			{
				errorFlag = FADriver(passedString, lineNumber);

				//Stops program if error detected.		
				if(errorFlag == 1)
				{
					return;
				}		

				lineNumber++;
				passedString = "";
				inputHolder = "";
				break;
			}
			else if(inputHolder[index] == '$')
			{
				index++;

				if(inputHolder[index] == '$')
				{
					commentFlag += 1;		
					index++;	
			
					if(commentFlag == 2)
					{
						commentFlag = 0;
					}
				}
				else
				{
					std::cout << "Error has occured with comment syntax." << std::endl;
					return;
				}
			}
			else
			{
				index++;
			}		
		}
	}
	
	//Issued a end of token since file ended.
	errorFlag = FADriver("EOF", lineNumber);

	//Stops program if error detected.		
	if(errorFlag == 1)
	{
		return;
	}
	
	node *tree = parser();

	std::ofstream outFile(keyboardFile.c_str());

	if(outFile == NULL)
	{
		std::cout << "Unable to create/write to file." << std::endl;
		exit(1);
	}

	recGen(tree, outFile);
	
	outFile.close();
}

