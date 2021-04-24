//Author: Timothy Schultz
//CS 4280
//Project 3

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "generator.h"
#include "node.h"

//P3 Static Variables
static DynamicStack r;
static int globalVar = 0;
static int numberVar = 0;
static int totalVar = 0;
static int globalFlag = 0;
static int failFlag = 0;

//P4 Static Variables
static int LabelCntr = 0;
static int VarCntr = 0;

std::string newName(nameType what)
{	
	std::string name;
	std::ostringstream ex;

	if(what == VAR)
	{
		name = "T";
		ex << VarCntr;
		name += ex.str();
		VarCntr++;
	}
	else
	{
		name = "T";
		ex << LabelCntr;
		name += ex.str();
		LabelCntr++;
	}

	return name;
}

//Moves through the tree and operates the stack.
void recGen(node *holder)
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
		recGen(holder->child1);
		recGen(holder->child2);
		recGen(holder->child3);

		//Add stop to file
		std::cout << "STOP" << std::endl;

		//Need to create seperate stack to store both temp and 
		//declared variables at the end of the file.
	}
	else if(holder->label.compare("main") == 0)
	{
		//Flips to allow local variable count to start
		globalFlag = 1;

		//The node "main" does note contain any children.
	}
	else if(holder->label.compare("<vars>") == 0)
	{	
		node *temp = holder->child1;
		if(globalFlag == 0 && temp->label.compare("empty") != 0)
		{
			globalVar++;
			totalVar++;
		}
		else if(temp->label.compare("empty") != 0)
		{
			numberVar++;
			totalVar++;
		}

		if(temp->id_1 == 23 && temp->label.compare("empty") != 0)
		{
			r.push(temp->label, temp->value_1, temp->id_1, temp->lineNumber);
			recGen(holder->child2);
		}		
	}
	else if(holder->label.compare("<expr>") == 0)
	{
		if(holder->child2 != NULL)
		{
			std::string varHolder = "";

			//expr();
			recGen(holder->child3);
			
			varHolder += newName(VAR);
			std::cout << "STORE " << varHolder << std::endl;

			//N();
			recGen(holder->child1);
			std::cout << "SUB " << varHolder << std::endl;

			varHolder = "";
		}
		else
		{
			//N();
			recGen(holder->child1);
		}
	
	}
	else if(holder->label.compare("<N>") == 0)
	{
		if(holder->child2 != NULL)
		{
			if(holder->child2->id_1 == 12 && holder->child2 != NULL)
			{
				std::string varHolder = "";

				//N();
				recGen(holder->child3);

				varHolder += newName(VAR);
				std::cout << "STORE " << varHolder << std::endl;

				//A();
				recGen(holder->child1);
				std::cout << "DIV " << varHolder << std::endl;

				varHolder = "";
			}
			else if(holder->child2->id_1 == 11 && holder->child2 != NULL)
			{
				std::string varHolder = "";

				//N();
				recGen(holder->child3);

				varHolder += newName(VAR);
				std::cout << "STORE " << varHolder << std::endl;

				//A();
				recGen(holder->child1);
				std::cout << "MULT " << varHolder << std::endl;

				varHolder = "";
			}
		}
		else
		{
			//A();
			recGen(holder->child1);
		}

	}
	else if(holder->label.compare("<A>") == 0)
	{
		if(holder->child2 != NULL)
		{
			std::string varHolder = "";

			//A();
			recGen(holder->child3);
			
			varHolder += newName(VAR);
			std::cout << "STORE " << varHolder << std::endl;

			//M();
			recGen(holder->child1);
			std::cout << "ADD " << varHolder << std::endl;

			varHolder = "";
		}
		else
		{
			//M();
			recGen(holder->child1);
		}
	}
	else if(holder->label.compare("<M>") == 0)
	{
		if(holder->child2 != NULL)
		{
			//M();
			recGen(holder->child3);
			
			//Negate number by changing sign
			std::cout << "MULT -1" << std::endl;
		}
		else
		{
			//R();
			recGen(holder->child1);
		}
	}
	else if(holder->label.compare("<R>") == 0)
	{
		if(holder->child1->id_1 == 23)
		{
			r.searchDeclaration(holder->child1->value_1);

			//Stack output needed.
		}
		else if(holder->child1->id_1 == 24)
		{
			std::cout << "LOAD " << holder->child1->value_1 << std::endl;
		}
		else
		{
			//(expr())
			recGen(holder->child1);
		}
	}
	/*
	else if(holder->label.compare("<in>") == 0)
	{
		//When in is detected get the child information and search stack.
		node *temp = holder->child1;
		if(temp->id_1 == 23)
		{
			//Check to see if declared
			r.searchDeclaration(temp->value_1);
			std::cout << "READ " << temp->value_1 << std::endl;
		}

		//Recursive call to children.
		recGen(holder->child2);
		recGen(holder->child3);
		recGen(holder->child4);
		recGen(holder->child5);

	}
	else if(holder->label.compare("<assign>") == 0)
	{
		//When assign is detected get the child information and push to stack.
		node *temp = holder->child1;	
		if(temp->id_1 == 23)
		{
			//Check to see if declared
			r.searchDeclaration(temp->value_1);
			std::cout << temp->value_1 << " "; 
		}

		//Recursive call to children.
		recGen(holder->child1);
		recGen(holder->child2);
		recGen(holder->child3);
		recGen(holder->child4);
		recGen(holder->child5);
	}
	else if(holder->label.compare("<label>") == 0)
	{
		//When label is detected get the child information and push to stack.
		node *temp = holder->child1;
		if(temp->id_1 == 23)
		{
			//Check to see if declared
			r.searchDeclaration(temp->value_1);
		}

		//Recursive call to children.
		recGen(holder->child1);
		recGen(holder->child2);
		recGen(holder->child3);
		recGen(holder->child4);
		recGen(holder->child5);
	}	
	else if(holder->label.compare("<goto>") == 0)
	{
		//When goto is detected get the child information and push to stack.
		node *temp = holder->child1;
		if(temp->id_1 == 23)
		{
			//Check to see if declared
			r.searchDeclaration(temp->value_1);
		}

		//Recursive call to children.
		recGen(holder->child1);
		recGen(holder->child2);
		recGen(holder->child3);
		recGen(holder->child4);
		recGen(holder->child5);
	}
	*/
	else
	{
		//Recursive call to children.
		recGen(holder->child1);
		recGen(holder->child2);
		recGen(holder->child3);
		recGen(holder->child4);
		recGen(holder->child5);
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
		/*
		if(failFlag == 0)
		{
			std::cout << "Popping off stack: " << currentPtr->label << std::endl;
		}
		*/		

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
		}
		else
		{
			//std::cout << "Pushed to stack: " << nodeCreated->label << std::endl;
			nodeCreated->next = top;
			top = nodeCreated;
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
				//std::cout << "Search error 1" << std::endl;
				errorStack(holder, n, " ", 1, holder->lineNumber);
			}
		}
		else
		{
			if(holder->id == n->id && holder->symbol.compare(n->symbol) == 0)
			{
				//std::cout << "Search error 2" << std::endl;
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

	if(holder == NULL)
	{
		//std::cout << "Search Dec error 1" << std::endl;
		errorStack(holder, holder, symbol, 2, -1);
	}

	while(holder != NULL)
	{
		if(holder->symbol.compare(symbol) == 0)
		{
			return true;
		}

		holder = holder->next;	
	}

	//std::cout << "Search Dec error 2" << std::endl;
	errorStack(holder, holder, symbol, 2, lineNum);
	return false;
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
		failFlag = 1;
		exit(1);
	}	
	else if(flag == 2)
	{
		std::cout << "Identifier " << symbol << " was not declared." << std::endl;
		failFlag = 1;
		exit(1);
	}
	else
	{
		failFlag = 1;
		exit(1);
	}
}
