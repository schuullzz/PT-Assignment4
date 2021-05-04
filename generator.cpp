//Author: Timothy Schultz
//CS 4280
//Project 4

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "generator.h"
#include "node.h"

//*************P3 Static Variables**************
//Stack used for variables.
static DynamicStack r;
//Number of global variables.
static int globalVar = 0;
//Number of scoped variables.
static int numberVar = 0;
//Number of total variables.
static int totalVar = 0;
//Keeps track if there are any global variables 
//and when they end.
static int globalFlag = 0;

//*************P4 Static Variables**************
//Keeps track of the number of temporary lables.
static int LabelCntr = 0;
//Keeps track of the number of temporary variables.
static int VarCntr = 0;
//Keeps track of the index of the stack.
static int stackIndex;
//Keeps track of label index for label function.
static int labelIndex = 0;
//Keeps track of the temp variables used to set to zero
//at the end of program.
static std::vector<std::string> initVars;
static std::vector<std::string> initLabels;
//Holds the name of file to be deleted if error occurs.
extern std::string fileDelete;

//Function that creates temp variable names and labels.
//Taken from class notes.
std::string newName(nameType what)
{	
	//Contains concatenated string to be returened.
	std::string name;
	//Stream object to push number into name.
	std::ostringstream ex;

	//If else that determines to either create temp var or 
	//label.
	if(what == VAR)
	{
		name = "T";
		ex << VarCntr;
		name += ex.str();
		initVars.push_back(name);
		VarCntr++;
	}
	else
	{
		name = "L";
		ex << LabelCntr;
		name += ex.str();
		LabelCntr++;
	}

	return name;
}

//Moves through the tree and operates the stack. 
void recGen(node *holder, std::ofstream &outFile)
{
	//if tree holder points to null return
	if(holder == NULL)
	{
		return;
	}	
	
	//If statements that operate the function to be called in the stack.
	if(holder->label.compare("<program>") == 0)
	{
		//Contains only three children 
		recGen(holder->child1, outFile);
		recGen(holder->child2, outFile);
		recGen(holder->child3, outFile);

		for(int x = 0; x < totalVar; x++)
		{
			r.pop();
			outFile << "POP\n";	
		}

		//Add stop to file
		//std::cout << "STOP" << std::endl;
		outFile << "STOP\n";

		//Need to create seperate stack to store both temp and 
		//declared variables at the end of the file.
		
		//Contains the size of the temp variable vec size.
		int sizeVec = initVars.size();

		//Prints out the temp variables with zero at the end of program.
		for(int index = 0; index < sizeVec; index++)
		{
			//std::cout << initVars.at(index) << " 0" << std::endl;
			outFile << initVars.at(index) << " 0\n";
		}

	}
	else if(holder->label.compare("main") == 0)
	{
		//Flips to allow local variable count to start
		globalFlag = 1;

		//The node "main" does note contain any children.
	}
	else if(holder->label.compare("<vars>") == 0)
	{	
		//If else that determines if current variable is global or scoped and increments 
		//correct variable.
		if(globalFlag == 0 && holder->child1->label.compare("empty") != 0)
		{
			globalVar++;
			totalVar++;
		}
		else if(holder->child1->label.compare("empty") != 0)
		{
			numberVar++;
			totalVar++;
		}

		//If statement that records declared variable with PUSH, LOAD, and STACKW.
		if(holder->child1->id_1 == 23 && holder->child1->label.compare("empty") != 0)
		{
			//Pushed on stack r with variables information also checking if already declared.
			r.push(holder->child1->label, holder->child1->value_1, holder->child1->id_1, holder->child1->lineNumber);
			//Searches stack to see the index of variable
			r.searchDeclaration(holder->child1->value_1);

			//std::cout << "PUSH" << std::endl;
			//std::cout << "LOAD " << holder->child1->value_3 << std::endl;
			//std::cout << "STACKW " << 0 << std::endl;

			outFile << "PUSH\n";
			outFile << "LOAD " << holder->child1->value_3 << "\n";
			outFile << "STACKW " << stackIndex << "\n";  
			
			//recursive call passing child 2.
			recGen(holder->child2, outFile);
		}
	}
	else if(holder->label.compare("<expr>") == 0)
	{
		//If else determining if negative operator was used other wise
		//recursively call passing child1.
		if(holder->child2 != NULL)
		{
			std::string varHolder = "";

			//expr();
			recGen(holder->child3, outFile);
			
			//Creates new temp variable.
			varHolder += newName(VAR);
			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//N();
			recGen(holder->child1, outFile);
			//std::cout << "SUB " << varHolder << std::endl;
			outFile << "SUB " << varHolder << "\n";

			varHolder = "";
		}
		else
		{
			//N();
			recGen(holder->child1, outFile);
		}
	
	}
	else if(holder->label.compare("<N>") == 0)
	{
		//If statement that checks if child2 points to null or not. If Null
		//recursive call passing child1.
		if(holder->child2 != NULL)
		{
			//Checks to see if division or multiplication operator.
			if(holder->child2->id_1 == 12 && holder->child2 != NULL)
			{
				std::string varHolder = "";

				//N();
				recGen(holder->child3, outFile);

				//Creates new variable.
				varHolder += newName(VAR);
				//std::cout << "STORE " << varHolder << std::endl;
				outFile << "STORE " << varHolder << "\n";

				//A();
				recGen(holder->child1, outFile);
				//std::cout << "DIV " << varHolder << std::endl;
				outFile << "DIV " << varHolder << "\n";

				varHolder = "";
			}
			else if(holder->child2->id_1 == 11 && holder->child2 != NULL)
			{
				std::string varHolder = "";

				//N();
				recGen(holder->child3, outFile);

				varHolder += newName(VAR);
				//std::cout << "STORE " << varHolder << std::endl;
				outFile << "STORE " << varHolder << "\n";

				//A();
				recGen(holder->child1, outFile);
				//std::cout << "MULT " << varHolder << std::endl;
				outFile << "MULT " << varHolder << "\n";

				varHolder = "";
			}
		}
		else
		{
			//A();
			recGen(holder->child1, outFile);
		}

	}
	else if(holder->label.compare("<A>") == 0)
	{
		//Checks to see if child2 is Null or has children. If null
		//recursively call passing child1.
		if(holder->child2 != NULL)
		{
			std::string varHolder = "";

			//A();
			recGen(holder->child3, outFile);
			
			//Creates new temp variable.
			varHolder += newName(VAR);
			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//M();
			recGen(holder->child1, outFile);
			//std::cout << "ADD " << varHolder << std::endl;
			outFile << "ADD " << varHolder << "\n";

			varHolder = "";
		}
		else
		{
			//M();
			recGen(holder->child1, outFile);
		}
	}
	else if(holder->label.compare("<M>") == 0)
	{
		//Checks to see if child2 points to Null. If Null
		//recursive call passing child1.
		if(holder->child2 != NULL)
		{
			//M();
			recGen(holder->child3, outFile);
			
			//Negate number by changing sign
			//std::cout << "MULT -1" << std::endl;
			outFile << "MULT -1\n";
		}
		else
		{
			//R();
			recGen(holder->child1, outFile);
		}
	}
	else if(holder->label.compare("<R>") == 0)
	{
		//Checks to see if identifier, integer, or parentheses. If parentheses the
		//recursive call passing child1.
		if(holder->child1->id_1 == 23)
		{
			//Finds index if declared.
			r.searchDeclaration(holder->child1->value_1);

			//Stack output
			//std::cout << "STACKR " << stackIndex << std::endl;	
			outFile << "STACKR " << stackIndex << "\n";
		}
		else if(holder->child1->id_1 == 24)
		{
			//std::cout << "LOAD " << holder->child1->value_1 << std::endl;
			outFile << "LOAD " << holder->child1->value_1 << "\n";
		}
		else
		{
			//(expr())
			recGen(holder->child1, outFile);
		}
	}
	else if(holder->label.compare("<in>") == 0)
	{
		if(holder->child1->id_1 == 23)
		{
			//Creates new temp variable.
			std::string varHolder = "";
			varHolder += newName(VAR);

			//Check to see if declared
			r.searchDeclaration(holder->child1->value_1);
		
			//std::cout << "READ " << varHolder << std::endl;
			//std::cout << "LOAD " << varHolder << std::endl;
			//std::cout << "STACKW " << stackIndex << std::endl;

			outFile << "READ " << varHolder << "\n";
			outFile << "LOAD " << varHolder << "\n";
			outFile << "STACKW " << stackIndex << "\n";
		}
	}
	else if(holder->label.compare("<out> outter") == 0)
	{
		//expr();
		recGen(holder->child1, outFile);
		
		//Creates new temp variable.
		std::string varHolder = "";
		varHolder += newName(VAR);

		//std:: cout << "STORE " << varHolder << std::endl;
		//std:: cout << "WRITE " << varHolder << std::endl;

		outFile << "STORE " << varHolder << "\n";
		outFile << "WRITE " << varHolder << "\n";

	}
	else if(holder->label.compare("<if>") == 0)
	{
		//expr();
		recGen(holder->child3, outFile);

		//Creates a new temp label.
		std::string labHolder = newName(LABEL);

		//RO operators. If =>, =<, ==, or [==]. Subtracts second variable
		//from first and determines what branch is necessary. For % checks
		//to see if signs of int are opposite. 
		if(holder->child2->child1->id_1 == 4)
		{
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRZNEG " << labHolder << std::endl;
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRZNEG " << labHolder << "\n";
		}
		else if(holder->child2->child1->id_1 == 5)
		{	
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRZPOS " << labHolder << std::endl;
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRZPOS " << labHolder << "\n";
		}
		else if(holder->child2->child1->id_1 == 3)
		{
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRNEG " << labHolder << std::endl; 
			//std::cout << "BRPOS " << labHolder << std::endl; 
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRNEG " << labHolder << "\n";
			outFile << "BRPOS " << labHolder << "\n";
		}
		else if(holder->child2->child1->id_1 == 27)
		{
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRZERO " << labHolder << std::endl;
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRZERO " << labHolder << "\n";
		}
		else if(holder->child2->child1->id_1 == 13)
		{
			//Creates new temp var.
			std::string varHolder1 = newName(VAR);
			//Creates new temp var.
			std::string varHolder2 = newName(VAR);
			//Creates new temp label.
			std::string mod1 = newName(LABEL);
			//Creates new temp label.
			std::string mod2 = newName(LABEL);
			//Creates new temp label.
			std::string mod3 = newName(LABEL);

			//std::cout << "STORE " << varHolder1 << std::endl;
			outFile << "STORE " << varHolder1 << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "STORE " << varHolder2 << std::endl;
			//std::cout << "LOAD " << varHolder1 << std::endl;
			//std::cout << "BRNEG " << mod1 << std::endl;
			//std::cout << "BRPOS " << mod2 << std::endl;
			//std::cout << mod1 << ": NOOP" << std::endl;
			//std::cout << "LOAD " << varHolder2 << std::endl;
			//std::cout << "BRNEG " << labHolder << std::endl;
			//std::cout << "BR " << mod3 << std::endl;
			//std::cout << mod2 << ": NOOP" << std::endl;
			//std::cout << "BRPOS " << labHolder << std::endl;
			//std::cout << "BR " << mod3 << std::endl;
			//std::cout << mod3 << ": NOOP" << std::endl;

			outFile << "STORE " << varHolder2 << "\n";
			outFile << "LOAD " << varHolder1 << "\n";
			outFile << "BRNEG " << mod1 << "\n";
			outFile << "BRPOS " << mod2 << "\n";
			outFile << mod1 << ": NOOP" << "\n";
			outFile << "LOAD " << varHolder2 << "\n";
			outFile << "BRNEG " << labHolder << "\n";
			outFile << "BR " << mod3 << "\n";
			outFile << mod2 << ": NOOP" << "\n";
			outFile << "BRPOS " << labHolder << "\n";
			outFile << "BR " << mod3 << "\n";
			outFile << mod3 << ": NOOP" << "\n";
		}

		
		recGen(holder->child5, outFile);
		//std::cout << labHolder << ": NOOP" << std::endl;
		outFile << labHolder << ": NOOP\n";

	}
	else if(holder->label.compare("<loop>") == 0)
	{
		//Creates new temp label.
		std::string beginLoop = newName(LABEL);
		//Creates new temp label.
		std::string endLoop = newName(LABEL);
		//Creates new temp label.
		std::string mod1 = newName(LABEL);
		//Creates new temp label.
		std::string mod2 = newName(LABEL);
		//Creates new temp label.
		std::string brOut = newName(LABEL);
		//std::cout << beginLoop << ": ";
		outFile << beginLoop << ": NOOP\n";
	
		//expr();
		recGen(holder->child3, outFile);

		//RO operators
		if(holder->child2->child1->id_1 == 4)
		{
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRZNEG " << endLoop << std::endl;
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRZNEG " << endLoop << "\n";
		}
		else if(holder->child2->child1->id_1 == 5)
		{
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRZPOS " << endLoop << std::endl;
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRZPOS " << endLoop << "\n";
		}
		else if(holder->child2->child1->id_1 == 3)
		{
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRNEG " << endLoop << std::endl;
			//std::cout << "BRPOS " << endLoop << std::endl;
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRNEG " << endLoop << "\n";
			outFile << "BRPOS " << endLoop << "\n";
		}
		else if(holder->child2->child1->id_1 == 27)
		{
			//Creates new temp var.
			std::string varHolder = newName(VAR);

			//std::cout << "STORE " << varHolder << std::endl;
			outFile << "STORE " << varHolder << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "SUB " << varHolder << std::endl;
			//std::cout << "BRZERO " << endLoop << std::endl; 
			outFile << "SUB " << varHolder << "\n";
			outFile << "BRZERO " << endLoop << "\n"; 
		}
		else if(holder->child2->child1->id_1 == 13)
		{
			//Creates new temp var.
			std::string varHolder1 = newName(VAR);
			//Creates new temp var.
			std::string varHolder2 = newName(VAR);

			//std::cout << "STORE " << varHolder1 << std::endl;
			outFile << "STORE " << varHolder1 << "\n";

			//expr();
			recGen(holder->child1, outFile);

			//std::cout << "STORE " << varHolder2 << std::endl;
			//std::cout << "LOAD " << varHolder1 << std::endl;
			//std::cout << "BRNEG " << mod1 << std::endl;
			//std::cout << "BRPOS " << mod2 << std::endl;
			//std::cout << mod1 << ": NOOP" << std::endl;
			//std::cout << "LOAD " << varHolder2 << std::endl;
			//std::cout << "BRNEG " << endLoop << std::endl;
			//std::cout << "BR " << brOut << std::endl;
			//std::cout << mod2 << ": NOOP" << std::endl;
			//std::cout << "BRPOS " << endLoop << std::endl;
			//std::cout << "BR " << brOut << std::endl;
			//std::cout << brOut << ": NOOP" << std::endl;
			
			outFile << "STORE " << varHolder2 << "\n";
			outFile << "LOAD " << varHolder1 << "\n";
			outFile << "BRNEG " << mod1 << "\n";
			outFile << "BRPOS " << mod2 << "\n";
			outFile << mod1 << ": NOOP" << "\n";
			outFile << "LOAD " << varHolder2 << "\n";
			outFile << "BRNEG " << endLoop << "\n";
			outFile << "BR " << brOut << "\n";
			outFile << mod2 << ": NOOP" << "\n";
			outFile << "BRPOS " << endLoop << "\n";
			outFile << "BR " << brOut << "\n";
			outFile << brOut << ": NOOP" << "\n";
		}

		//stat()
		recGen(holder->child4, outFile);

		//std::cout << "BR " << beginLoop << std::endl;
		//std::cout << endLoop << ": NOOP" << std::endl;
		outFile << "BR " << beginLoop << "\n";
		outFile << endLoop << ": NOOP\n";
	}
	else if(holder->label.compare("<assign>") == 0)
	{
		//expr();
		recGen(holder->child2, outFile);

		if(holder->child1->id_1 == 23)
		{
			//Check to see if declared
			r.searchDeclaration(holder->child1->value_1);

			//<< "STACKW " << stackIndex << std::endl;
			outFile << "STACKW " << stackIndex << "\n";
		}

	}
	else if(holder->label.compare("<label>") == 0)
	{
		if(holder->child1->id_1 == 23)
		{
			//Creates a temp label based on identifer.
			std::string labelName = "";
			labelName += holder->child1->value_1;
			
			//Makes sure label has not already been used (Identifier);
			if(r.vectorIndex(labelName) == -1)
			{			
				initLabels.push_back(labelName);
			}
			else
			{
				std::cout << "Error label already created." << std::endl;
				std::cout << "Deleting file " << fileDelete << "." << std::endl;	
				remove(fileDelete.c_str());
				exit(1);
			}

			//std::cout << labelName << ": NOOP" << std::endl;
			outFile << labelName << ": NOOP\n";
		}

	}
	else if(holder->label.compare("<goto>") == 0)
	{
		if(holder->child1->id_1 == 23)
		{
			//Creates a temp label based on identifer.
			std::string labelName = "";
			labelName += holder->child1->value_1;
	
			//Finds Index of label.
			int vecIndex = r.vectorIndex(labelName); 
	
			//If true an error has occured since a label has not been created.	
			if(vecIndex == -1)
			{
				std::cout << "Error Void Identifier was not found to create label to branch to." << std::endl;
				std::cout << "Deleting file " << fileDelete << "." << std::endl;	
				remove(fileDelete.c_str());
				exit(1);
			}


			//std::cout << "BR " << labelName << std::endl;			
			outFile << "BR " << labelName << "\n";			
		}

	}
	else
	{
		//Recursive call to children.
		recGen(holder->child1, outFile);
		recGen(holder->child2, outFile);
		recGen(holder->child3, outFile);
		recGen(holder->child4, outFile);
		recGen(holder->child5, outFile);
	}
	
}

//*************************************************************************************

//Destructor: Removes remaining nodes
DynamicStack::~DynamicStack()
{
	//std::cout << "Destructor called" << std::endl;

	//Nodes to hold values while clearing.
	StackNode *currentPtr = NULL;
	StackNode *nextNode = NULL;

	//Assign pointer to top of stack. 
	currentPtr = top;

	//Remove nodes from stack
	while(currentPtr != NULL)
	{
		nextNode = currentPtr->next;
		delete currentPtr;
		currentPtr = nextNode;
	}
}

//*************************************************************************************

//Push function: Pushes node ontop of the stack.
//Will check to see if identifier was already declared.
void DynamicStack::push(std::string label, std::string symbol, int id, int lineNumber)
{
	//Creates a new node
	StackNode *nodeCreated = NULL;

	//Fills the values for the created node.
	nodeCreated = new StackNode;
	nodeCreated->label = label;
	nodeCreated->symbol = symbol;
	nodeCreated->id = id;
	nodeCreated->lineNumber = lineNumber;
	
	//If no node is found placed on top or if node exists
	//placed in next.
	if(!search(nodeCreated))
	{
		if(isEmpty())
		{
			//std::cout << "Pushed to empty stack: " << nodeCreated->label << std::endl;
			top = nodeCreated;
			nodeCreated->next = NULL;
			
			if(!r.vectorDeclaration(symbol))
			{
				initVars.push_back(symbol);
			}
		}
		else
		{
			//std::cout << "Pushed to stack: " << nodeCreated->label << std::endl;
			nodeCreated->next = top;
			top = nodeCreated;

			if(!r.vectorDeclaration(symbol))
			{
				initVars.push_back(symbol);
			}
		}
	}
}

//**************************************************************************************

//Pop function: Will remove top node of stack
void DynamicStack::pop()
{
	//Holds a temp node.
	StackNode *holder = NULL;

	//If stack is empty return
	if(isEmpty())
	{
		//std::cout <<"Stack was empty." << std::endl;
		return;
	}
	else
	{
		//std::cout << "Poping off stack: " << top->label << std::endl;
		holder = top->next;
		delete top;
		top = holder;
	}
}

//**************************************************************************************

//Empty function: Checks to see if stack is empty
bool DynamicStack::isEmpty()
{
	//Holds value if stack is empty or not.
	bool result;

	if(!top)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

//**************************************************************************************

//Search function: Searches stack to make sure identifier was not already on stack
bool DynamicStack::search(StackNode *n)
{
	int variables = numberVar;
	int globals = globalVar;
	int totalVariables = totalVar;
	StackNode *holder;
	holder = top;

	if(holder == NULL)
	{
		return false;
	}

	while(holder != NULL)
	{
		if(globalFlag == 1)
		{
			totalVariables--;
		
			if(totalVariables <= globals || variables == 0)
			{
				break;
			}

			if(holder->id == n->id && holder->symbol.compare(n->symbol) == 0)
			{
				errorStack(holder, n, " ", 1, holder->lineNumber);
			}
		}
		else
		{
			if(holder->id == n->id && holder->symbol.compare(n->symbol) == 0)
			{
				errorStack(holder, n, " ", 1, holder->lineNumber);
			}

		}

		holder = holder->next;
	}

	return false;
}

//**************************************************************************************

//Search declaration function: Checks to make sure identifier was defined before use.
bool DynamicStack::searchDeclaration(std::string symbol)
{
	StackNode *holder;
	holder = top;
	int lineNum = 0;
	stackIndex = 0;

	if(holder == NULL)
	{
		errorStack(holder, holder, symbol, 2, -1);
	}
	
	holder = top;

	while(holder != NULL)
	{	
		if(holder->symbol.compare(symbol) == 0)
		{
			return true;
		}

		stackIndex++;	
		holder = holder->next;	
	}

	errorStack(holder, holder, symbol, 2, lineNum);
	return false;
}

//**************************************************************************************

bool DynamicStack::vectorDeclaration(std::string symbol)
{
	StackNode *holder;
	holder = top;
	int lineNum = 0;

	if(holder == NULL)
	{
		return false;
	}

	while(holder != NULL)
	{
		if(holder->symbol.compare(symbol) == 0)
		{
			return true;
		}

		holder = holder->next;	
	}

	return false;
}

//**************************************************************************************

int DynamicStack::vectorIndex(std::string sentence)
{
	for(int x = 0; x < initLabels.size(); x++)
	{
		if(sentence.compare(initLabels.at(x)) == 0)
		{
			return x;
		}

	}

	return -1;
}


//**************************************************************************************

//topStack: Returns what is on top of the stack.
std::string DynamicStack::topStack()
{
	return top->symbol;
}

//**************************************************************************************

//Error stack: returns appropriate error message.
void DynamicStack::errorStack(StackNode *holder, StackNode *n, std::string symbol, int flag, int lineNum)
{
	if(flag == 1)
	{
		std::cout << "Identifier error found on line: " << n->lineNumber << "." << std::endl;
		std::cout << "Identifier " << holder->symbol << " was declared on line: " << holder->lineNumber << "." << std::endl;
		exit(1);
	}	
	else if(flag == 2)
	{
		std::cout << "Identifier " << symbol << " was not declared." << std::endl;
		exit(1);
	}
	else
	{
		exit(1);
	}
}
