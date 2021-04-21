//Author: Timothy Schultz
//CS 4280
//Project 4

#ifndef NODE_H
#define NODE_H

#include <string>
#include "scanner.h"

struct node
{
	//Word stored in current node.
	std::string label;
	//token values
	int id_1;
	int id_2;
	int id_3;
	std::string value_1;
	std::string value_2;
	std::string value_3;
	int lineNumber;
	//Max five children
	node *child1 = NULL;
	node *child2 = NULL;
	node *child3 = NULL;
	node *child4 = NULL;
	node *child5 = NULL;
};

#endif
