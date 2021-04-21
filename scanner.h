//Author: Timothy Schultz
//CS 4280
//Project 4

#ifndef SCANNER_H
#define SCANNER_H

#include <string>

//Enum for State and Row Position
enum stateT {S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, S21, S22, S23, S24, S25, S26, S27, FINAL, ERROR};

//Token Structure
struct tokenType
{
	stateT id;
	std::string symbol;
	std::string tokenInstance;
	int lineNumber;
};

//Prototypes
int errorScanner(int, int);
int FADriver(std::string, int);

#endif
