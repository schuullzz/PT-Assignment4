//Author: Timothy Schultz
//CS 4280
//Project 4

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "scanner.h"
#include "parser.h"
#include "node.h"

//Static globals
static int index;

//Extern Global 
extern std::vector<tokenType> tokenVec;

//Error function that identifies the missing tokens and line number.
void parserError(int flag , int numberLine)
{
	if(flag == 1)
	{
		std::cout << "Missing Key Token main or Illegal Statement before Key Token main." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 2)
	{
		std::cout << "Missing Identifier Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 3)
	{
		std::cout << "Missing Assignment Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 4)
	{
		std::cout << "Missing Integer Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 5)
	{
		std::cout << "Missing Semicolon Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 6)
	{
		std::cout << "Missing Key Word Token begin" << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 7)
	{
		std::cout << "Missing Key Word Token end" << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 8)
	{
		std::cout << "Missing Key Word Token" << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 9)
	{
		std::cout << "Missing Left Parenthesis Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 10)
	{
		std::cout << "Missing Right Parenthesis Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 11)
	{
		std::cout << "Missing Left Bracket Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 12)
	{
		std::cout << "Missing Right Bracket Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 13)
	{
		std::cout << "Missing Operator Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 14)
	{
		std::cout << "Missing Equivalent Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 15)
	{
		std::cout << "Missing Token." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else if(flag == 16)
	{
		std::cout << "Missing Key Word Token then." << std::endl;
		std::cout << "Line Number: " << numberLine <<  std::endl;
	}
	else
	{
		return;
	}

	exit(1);

}

node* getNode(std::string info, int id_1, int id_2, int id_3, std::string value_1, std::string value_2, std::string value_3, int lineNumber)
{
	node *holder = new node;
	holder->label = info;
	holder->id_1 = id_1;
	holder->id_2 = id_2;
	holder->id_3 = id_3;
	holder->value_1 = value_1;
	holder->value_2 = value_2;
	holder->value_3 = value_3;
	holder->lineNumber = lineNumber;
	return holder;
}

//Parser Function: calls program function <program>
//Ends program when EOF token is detected.
node* parser()
{	
	//root of tree
	node* root;

	//Calls program function
	root = program();

	//If statement that detects EOF token 
	if(tokenVec[index].id == 26)
	{
		//std::cout << "EOF" << std::endl;			
		return root;
	}
	else
	{
	       return root;		
	}
}

//Program Function: <vars> main <block>
node* program()
{
	//get node
	node* node_ex = getNode("<program>", -1, -1, -1, "", "", "", -1);

	//Calls vars function
	node_ex->child1 = vars();

	//If statement that detects if main token is used.
	if(tokenVec[index].id == 25)
	{
		if((tokenVec[index].symbol).compare("main") == 0)
		{
			node_ex->child2 = getNode("main", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
			node_ex->child3 = block();
		}
		else
		{
	       		parserError(1, tokenVec[index].lineNumber);
		}
	}
	else
	{
	       	parserError(1, tokenVec[index].lineNumber);
	}

	return node_ex;
}

// empty | data Identifier := Integer ; <vars>
node* vars()
{
	//string holder
	std::string sentence = "";
	std::string ident = "";
	std::string oper = "";
	std::string integer = "";
	int lineCurrent;
	//get node
	node* node_ex = getNode("<vars>", -1, -1, -1, "", "", "", -1);

	//If statements that detexted if data Identifier := Integer ; 
	if(tokenVec[index].id == 25)
	{
		if((tokenVec[index].symbol).compare("data") == 0)
		{
			sentence += "data ";
			index++;

			if(tokenVec[index].id == 23)
			{
				sentence += tokenVec[index].symbol;
				sentence += " ";
				ident += tokenVec[index].symbol;
				lineCurrent = tokenVec[index].lineNumber;
				index++;

				if(tokenVec[index].id == 8)
				{
					sentence += tokenVec[index].symbol;
					sentence += " ";
					oper += tokenVec[index].symbol;
					index++;

					if(tokenVec[index].id == 24)
					{
						sentence += tokenVec[index].symbol;
						sentence += " ";
						integer += tokenVec[index].symbol;
						index++;
			
						if(tokenVec[index].id == 20)
						{
							sentence += tokenVec[index].symbol;
							node_ex->child1 = getNode(sentence, 23, 8, 24, ident, oper, integer, lineCurrent);
							index++;
							//std::cout << "data Identifier := Integer ; <vars>" << std::endl;
							node_ex->child2 = vars();
						}
						else
						{
							//error
	       						parserError(5, tokenVec[index].lineNumber);
						}
					}
					else
					{
						//error
	       					parserError(4, tokenVec[index].lineNumber);
					}
				}
				else
				{
					//error
	       				parserError(3, tokenVec[index].lineNumber);
				}
			}
			else
			{
				//error
	       			parserError(2, tokenVec[index].lineNumber);		
			}
		}
		else
		{
			//std::cout << "empty <var>" << std::endl;
			node_ex->child1 = getNode("empty", -1, -1, -1, "", "", "", -1);
		}
	}
	else
	{
		//std::cout << "empty <var>" << std::endl;
		node_ex->child1 = getNode("empty", -1, -1, -1, "", "", "", -1);
	}	
	
	return node_ex;
}

//begin <vars> <stats> end
node* block()
{
	//get node
	node* node_ex = getNode("<block>", -1, -1, -1, "", "", "", -1);

	//If statement that checks for begin token.
	if((tokenVec[index].symbol).compare("begin") == 0)
	{
		node_ex->child1 = getNode("begin", -1, -1, -1, "", "", "", tokenVec[index].lineNumber);
		//std::cout << "begin <vars> <stats>" << std::endl;

		index++;
			
		//Calls function vars
		node_ex->child2 = vars();
		//Calls function stats
		node_ex->child3 = stats();
			
		//If statement that checks for end token.
		if((tokenVec[index].symbol).compare("end") == 0)
		{
			node_ex->child4 = getNode("end", -1, -1, -1, "", "", "", tokenVec[index].lineNumber);
			//std::cout << "end" << std::endl;			
			index++;
		}
		else
		{
			//error
	       		parserError(7, tokenVec[index].lineNumber);
		}

	}
	else
	{
		//error
	       	parserError(6, tokenVec[index].lineNumber);
	}

	return node_ex;
}

// <stat> <mStat>
node* stats()
{
	//get node
	node* node_ex = getNode("<stats>", -1, -1, -1, "", "", "", -1);

	//std::cout << "<stat> <mStat>" << std::endl;
	//Calls stat function.
	node_ex->child1 = stat();
	//Calls mStat function.
	node_ex->child2 = mStat();

	return node_ex;
}

// empty | <stat> <mStat>
node* mStat()
{
	//get node
	node* node_ex = getNode("<mStat>", -1, -1, -1, "", "", "", -1);

	//If statement checks for identifier and that it is not an end token.
	if(tokenVec[index].id == 25 && (tokenVec[index].symbol).compare("end") != 0)
	{
		//std::cout << "<stat> <mStat> within mstat()" << std::endl;
		//Calls stat function.
		node_ex->child1 = stat();
		//Calls mStat function.
		node_ex->child2 = mStat();
		return node_ex;
	}
	else
	{
		//std::cout << "<mStat> -> empty" << std::endl;
		node_ex->child1 = getNode("empty", -1, -1, -1, "", "", "", -1);
		return node_ex;
	}

}

// <in>; | <out>; | <block>; | <if>; | <loop>; | <assign>; | <goto>; | <label>;
node* stat()
{
	//get node
	node* node_ex = getNode("<stat>", -1, -1, -1, "", "", "", -1);

	//If statement to determine which token was used.
	if((tokenVec[index].symbol).compare("getter") == 0)
	{	
		index++;
		node_ex->child1 = in();
		
		if(tokenVec[index].id == 20)
		{
			node_ex->child2 = getNode("<in>;", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
		}
		else
		{
			//error
	       		parserError(5, tokenVec[index].lineNumber);
		}

	}
	else if((tokenVec[index].symbol).compare("outter") == 0)
	{
		//std::cout << "outter" << std::endl;
		index++;
		node_ex->child1 = out();

		if(tokenVec[index].id == 20)
		{
			node_ex->child2 = getNode("<out>;", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
		}
		else
		{
			//error
	       		parserError(5, tokenVec[index].lineNumber);
		}
	}
	else if((tokenVec[index].symbol).compare("begin") == 0)
	{
		//std::cout << "begin" << std::endl;
		node_ex->child1 = block();
	}
	else if((tokenVec[index].symbol).compare("if") == 0)
	{
		index++;
		node_ex->child1 = IF();

		if(tokenVec[index].id == 20)
		{
			node_ex->child2 = getNode("<if>;", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
		}
		else
		{
			//error
	       		parserError(5, tokenVec[index].lineNumber);
		}
	}
	else if((tokenVec[index].symbol).compare("loop") == 0)
	{
		index++;
		node_ex->child1 = loop();

		if(tokenVec[index].id == 20)
		{
			node_ex->child2 = getNode("<loop>;", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
		}
		else
		{
			//error
	       		parserError(5, tokenVec[index].lineNumber);
		}	
	}
	else if((tokenVec[index].symbol).compare("assign") == 0)
	{
		//std::cout << "assign" << std::endl;
		index++;
		node_ex->child1 = assign();

		if(tokenVec[index].id == 20)
		{
			node_ex->child2 = getNode("<assign>;", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
		}
		else
		{
			//error
	       		parserError(5, tokenVec[index].lineNumber);
		}
	}	
	else if((tokenVec[index].symbol).compare("proc") == 0)
	{
		//std::cout << "proc" << std::endl;
		index++;
		node_ex->child1 = goTo();

		if(tokenVec[index].id == 20)
		{
			node_ex->child2 = getNode("<goto>;", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
		}
		else
		{
			//error
	       		parserError(5, tokenVec[index].lineNumber);
		}
	}
	else if((tokenVec[index].symbol).compare("void") == 0)
	{
		//std::cout << "void" << std::endl;
		index++;
		node_ex->child1 = label();

		if(tokenVec[index].id == 20)
		{
			node_ex->child2 = getNode("<label>;", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
			index++;
		}
		else
		{
			//error
	       		parserError(5, tokenVec[index].lineNumber);
		}
	}
	else
	{
		std::cout << "Inside stat error" << std::endl;
	       	parserError(8, tokenVec[index].lineNumber);
	}

	return node_ex;
}

// getter Identifer
node* in()
{
	node *node_ex = getNode("<in>", -1, -1, -1, "", "", "", -1);
	//Chceks to see if identifer token was used.
	if(tokenVec[index].id == 23)
	{
		std::string sentence = "";
		sentence += "getter ";
		sentence += tokenVec[index].symbol;
		node_ex->child1 = getNode(sentence, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
	}
	else
	{
	       	parserError(2, tokenVec[index].lineNumber);	
	}

	return node_ex;	
}

//outer <expr>
node* out()
{	
	//std::cout << "<expr>" << std::endl;
	node* node_ex = getNode("<out> outter", 25, -1, -1, "outer", "", "", -1);
	//Calls expr function
	node_ex->child1 = expr();
	return node_ex;
}

//<N> - <expr> | <N>
node* expr()
{
	//get node
	node* node_ex = getNode("<expr>", -1, -1, -1, "", "", "", -1);
	node_ex->child1 = N();	

	//If statement checks for - token
	if(tokenVec[index].id == 10)
	{
		node_ex->child2 = getNode("-", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
		node_ex->child3 = expr();
	}

	return node_ex;
}

// <A> / <N> | <A> * <N> | <A>
node* N()
{
	//get node
	node* node_ex = getNode("<N>", -1, -1, -1, "", "", "", -1);

	//std::cout << "<A>";
	//std::cout << "Before A call: " << tokenVec[index].symbol << std::endl;
	//Calls A function
	node_ex->child1 = A();

	//If statements check if / or * token was used.
	if(tokenVec[index].id == 12)
	{
		node_ex->child2 = getNode("/", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);	
		index++;
		node_ex->child3 = N();
	}
	else if (tokenVec[index].id == 11)
	{
		node_ex->child2 = getNode("*", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);	
		index++;
		node_ex->child3 = N();
	}

	return node_ex;
}

//<M> + <A> | <M>
node* A()
{
	//get node
	node* node_ex = getNode("<A>", -1, -1, -1, "", "", "", -1);

	//std::cout << "<M> ";
	//std::cout << "Before M call: " << tokenVec[index].symbol << std::endl;
	//Calls M function
	node_ex->child1 = M();
	
	//If statement checks for + token
	if(tokenVec[index].id == 9)
	{
		node_ex->child2 = getNode("+", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);	
		index++;
		node_ex->child3 = A();
	}

	return node_ex;
}

//*<M> | <R>
node* M()
{
	//get node
	node* node_ex = getNode("<M>", -1, -1, -1, "", "", "", -1);

	//If statement checks for * token
	if (tokenVec[index].id == 11)
	{
		node_ex->child2 = getNode("*<M>", tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);	
		index++;
		node_ex->child3 = M();
	}
	else
	{
		node_ex->child1 = R();
	}

	return node_ex;
}

// (<expr>) | Identifier | Integer
node* R()
{
	//get node
	node* node_ex = getNode("<R>", -1, -1, -1, "", "", "", -1);	

	//std::cout << "Inside R" << std::endl;
	//std::cout << tokenVec[index].symbol << std::endl;

	//If statements that check for ( , Identifier, and Integer
	if(tokenVec[index].id == 15)
	{
		index++;
		node_ex->label += " (expr)";
		node_ex->child1 = expr();
		
		//If statement checks for ) token.
		if(tokenVec[index].id == 16)
		{
			index++;
		}
		else
		{
			//error
	       		parserError(10, tokenVec[index].lineNumber);
		}	
	}
	else if(tokenVec[index].id == 23)
	{
		node_ex->child1 = getNode(tokenVec[index].symbol, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
	}
	else if(tokenVec[index].id == 24)
	{
		node_ex->child1 = getNode(tokenVec[index].symbol, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
		//std::cout << "Integer" << std::endl;
	}
	else
	{
		//error
	       	parserError(9, tokenVec[index].lineNumber);	
	}

	return node_ex;
}

//if[<expr><R0><expr>]then<stat>
node* IF()
{
	//get node
	node* node_ex = getNode("<if>", -1, -1, -1, "", "", "", -1);

	//If statement checks for [ token
	if(tokenVec[index].id == 21)
	{
		index++;
		//Calls expr function
		node_ex->child1 = expr();
		//Calls R0 function
		node_ex->child2 = RO();
		//Calls expr function
		node_ex->child3 = expr();
		
		//If statement checks for ] token
		if(tokenVec[index].id == 22)
		{
			index++;
			if((tokenVec[index].symbol).compare("then") == 0)
			{
				index++;
				node_ex->child4 = getNode("then", -1, -1, -1, "", "", "", tokenVec[index].lineNumber);
				node_ex->child5 = stat();
			}
			else
			{
	       			parserError(16, tokenVec[index].lineNumber);	
			}
		}
		else
		{
			//error
	       		parserError(12, tokenVec[index].lineNumber);	
		}
	}
	else
	{
		//error
	       	parserError(11, tokenVec[index].lineNumber);		
	}	

	return node_ex;
}

// => | =< | == | [==] (three tokens) | %
node* RO()
{
	//get node
	node* node_ex = getNode("<R0>", -1, -1, -1, "", "", "", -1);

	if(tokenVec[index].id == 4)
	{	
		node_ex->child1 = getNode(tokenVec[index].symbol, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
	}
	else if(tokenVec[index].id == 5)
	{
		node_ex->child1 = getNode(tokenVec[index].symbol, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
	}
	else if(tokenVec[index].id == 3)
	{
		node_ex->child1 = getNode(tokenVec[index].symbol, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
	}
	else if(tokenVec[index].id == 21)
	{
		index++;
		if(tokenVec[index].id == 3)
		{
			index++;
			if(tokenVec[index].id == 22)
			{
				index++;
				node_ex->child1 = getNode("[==]", 3, -1, -1, "[==]", "", "", tokenVec[index].lineNumber);
			}
			else
			{
				//error
	       			parserError(12, tokenVec[index].lineNumber);
			}
		}
		else
		{
			//error
	       		parserError(14, tokenVec[index].lineNumber);
		}
	}
	else if(tokenVec[index].id == 13)
	{
		//std::cout << "%" << std::endl;
		node_ex->child1 = getNode(tokenVec[index].symbol, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
	}
	else
	{
		//error
	       	parserError(13, tokenVec[index].lineNumber);		
	}
	
	return node_ex;
}

//loop[<expr><R0><expr>]<stat>
node* loop()
{
	//get node
	node *node_ex = getNode("<loop>", -1, -1, -1, "", "", "", -1);

	//If statement checks for [ token
	if(tokenVec[index].id == 21)
	{
		//std::cout << "[<expr><RO><expr>" << std::endl;
		index++;
		//Calls expr function
		node_ex->child1 = expr();
		//Calls R0 function
		node_ex->child2 = RO();
		//Calls expr function
		node_ex->child3 = expr();
		
		//If statement checks for ] token
		if(tokenVec[index].id == 22)
		{
			//std::cout << "]" << std::endl;
			index++;
			node_ex->child4 = stat();
		}
		else
		{
			//error
	       		parserError(12, tokenVec[index].lineNumber);		
		}
	}
	else
	{
		//error
	       	parserError(11, tokenVec[index].lineNumber);		
	}

	return node_ex;
}

//assign Identifier := <expr>
node* assign()
{
	//get node
	node *node_ex = getNode("<assign>", -1, -1, -1, "", "", "", -1);

	int id_1;
	int id_2;
	std::string ident = "";
	std::string oper = "";
	std::string sentence = "";	
	sentence += "assign ";
	int lineCurrent;

	//If statement that checks for Identifier
	if(tokenVec[index].id == 23)
	{
		//std::cout << "Identifier" << std::endl;
		lineCurrent= tokenVec[index].lineNumber;
		id_1 = tokenVec[index].id;
		ident = tokenVec[index].symbol;
		sentence += tokenVec[index].symbol;
		sentence += " ";

		index++;

		//If statement that checks for := token
		if(tokenVec[index].id == 8)
		{
			//std::cout << ":=" << std::endl;
			id_2 = tokenVec[index].id;
			oper = tokenVec[index].symbol;
			sentence += tokenVec[index].symbol;
			sentence += " <expr>";
			node_ex->child1 = getNode(sentence, id_1, id_2, -1, ident, oper, "", lineCurrent);
			index++;
			//Calls expr function
			node_ex->child2 = expr();
		}
		else
		{
			//error
	       		parserError(3, tokenVec[index].lineNumber);		
		}
	}
	else
	{
		//error
	       	parserError(2, tokenVec[index].lineNumber);		
	}
	
	return node_ex;
}

//proc Identifier
node* goTo()
{
	//get node
	node *node_ex = getNode("<goto>",-1, -1, -1, "", "", "", -1);

	std::string sentence = "";
	sentence += "proc ";
	int id_1;
	std::string ident = "";

	//If statement checks for Identifier 
	if(tokenVec[index].id == 23)
	{
		sentence += tokenVec[index].symbol;
		id_1 = tokenVec[index].id;
		ident += tokenVec[index].symbol;

		node_ex->child1 = getNode(sentence, id_1, -1, -1, ident, "", "", tokenVec[index].lineNumber);
		//std::cout << "Identifier" << std::endl;
		index++;
	}
	else
	{
		//error
	       	parserError(2, tokenVec[index].lineNumber);		
	}

	return node_ex;
}

//void Identifier
node* label()
{
	//get node
	node *node_ex = getNode("<label>", -1, -1, -1, "", "", "", -1);

	std::string sentence = "";
	sentence += "void ";

	//If statement checks for Identifier 
	if(tokenVec[index].id == 23)
	{
		sentence += tokenVec[index].symbol;
		node_ex->child1 = getNode(sentence, tokenVec[index].id, -1, -1, tokenVec[index].symbol, "", "", tokenVec[index].lineNumber);
		index++;
	}
	else
	{
		//error
	       	parserError(2, tokenVec[index].lineNumber);		
	}

	return node_ex;

}

/*
//Print the tree
void print(node *holder, int depth)
{

	if(holder == NULL)
	{
		return;
	}


	for(int index = 0; index < depth; index++)
	{
		std::cout << "  ";
	}

	std::cout << holder->label << std::endl;

	depth++;
	print(holder->child1, depth);
	print(holder->child2, depth);
	print(holder->child3, depth);
	print(holder->child4, depth);
	print(holder->child5, depth);

}
*/
