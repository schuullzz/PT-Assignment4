//Author: Timothy Schultz
//CS 4280
//Project 4

#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include "node.h"

//enum types
typedef enum {VAR, LABEL} nameType;

//newName function
std::string newName(nameType);

//Prototype for driver for code generation.
void recGen(node *);

//Stack class
class DynamicStack
{
	private:

	//Structure for storing information about node.
	struct StackNode
	{
		std::string label;
		std::string symbol;
		int id;
		int lineNumber;	
		StackNode *next;
	};

	//Points to the top of the stack
	StackNode *top;

	public:

	//Constructor 
	DynamicStack()
	{
		top = NULL;
	}

	//Destructor 
	~DynamicStack();

	//Stack methods
	void push(std::string, std::string, int, int);
	void pop();
	bool isEmpty();
	bool search(StackNode *);
	bool searchDeclaration(std::string);
	bool vectorDeclaration(std::string);
	std::string topStack();
	void errorStack(StackNode *, StackNode *, std::string, int, int);
};

#endif
