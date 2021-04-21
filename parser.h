//Author: Timothy Schultz
//CS 4280
//Project 4

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "scanner.h"
#include "node.h"

void parserError(int, int);

node* getNode(std::string, int, int, int, std::string, std::string, std::string, int);
node* parser();
node* program();
node* vars();
node* block();
node* stats();
node* mStat();
node* stat();
node* in();
node* out();
node* expr();
node* N();
node* A();
node* M();
node* R();
node* IF();
node* RO();
node* loop();
node* assign();
node* goTo();
node* label();

//void print(node*, int);

#endif
