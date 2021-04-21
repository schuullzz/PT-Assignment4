//Author: Timothy Schultz
//CS 4280
//Project 4

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

//Column Position
char charColumn[] = {'=', '>', '<', ':', '+', '-', '*', '/', '%', '.', '(', ')', ',', '{', '}', ';', '[', ']', ' '}; 

//tokens
enum tokenId {WS_tk, EQUAL_tk, GT_tk, EQUIV_tk, GTOE_tk, LTOE_tk, LT_tk, COLON_tk, ASSIGN_tk, ADD_tk, SUB_tk, MULT_tk, DIV_tk, MOD_tk, PERIOD_tk, LPD_tk, 
RPD_tk, COMMA_tk, LCB_tk, RCB_tk, SEMCOL_tk, LSB_tk, RSB_tk, IDENT_tk, INT_tk, KW_tk, EOF_tk, F_tk, E_tk};

//String array of token names.
std::string tokeNames[] ={"White Space", "Equal Operator", "Greater Than Operator", "Equivalent Operator", "Greater Than or Equal Operator", "Less Than or Equal Operator", 
"Less Than Operator", "Colon Delimiter", "Assignment Operator", "Addition Operator", "Subtraction Operator", "Multiplication Operator", "Division Operator", "Modulus Operator", 
"Period Delimiter", "Left Parenthesis Delimiter", "Right Parenthesis Delimiter", "Comma Delimiter", "Left Curly Braces Delimiter", "Right Curly Braces Delimiter", "Semicolon Delimiter", 
"Left Square Bracket Delimiter", "Right Square Bracket Delimiter", "Identifier", "Integer", "Key Word", "End of File", "Final", "Error"};  

//String array of keywords.
std::string keyWords[] = {"begin", "end", "loop", "whole", "void", "exit", "getter", "outter", "main", "if", "then", "assign", "data", "proc"};

/*
	token id #
	----------
	=     | 1
	----------
	>     | 2
	----------
	==    | 3
	----------
	=>    | 4
	----------
	=<    | 5
	----------
	<     | 6
	----------
	:     | 7
	----------
	:=    | 8
	----------
	+     | 9
	----------
	-     | 10
	----------
	*     | 11
	----------
	/     | 12
	----------
	%     | 13
	----------
	.     | 14
	----------
	(     | 15
	----------
	)     | 16
	----------
	,     | 17
	----------
	{     | 18
	----------
	}     | 19
	----------
	;     | 20
	----------
	[     | 21
	----------
	]     | 22
	----------
	ident | 23
	----------
	Int   | 24
	----------
	KeyW  | 25
	----------
	EOF   | 26
	----------		

*/

/*
      =        >        <        :       +       -       *       /       %       .       (       )       ,       {       }       ;       [       ]       ws      ident   int
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
s1 |  s2    |  s3    |  s7     | s8    | s10   | s11   | s12   | s13   | s14   | s15   | s16   | s17   | s18   | s19   | s20   | s21   | s22   | s23   | FINAL | s24   | s25  |
s2 |  s4    |  s5    |  s6     | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk   | =tk  |
s3 |  >tk   |  >tk   |  >tk    | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk   | >tk  |
s4 |  ==tk  |  ==tk  |  ==tk   | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | ==tk  | =tk   | ==tk  | ==tk  | ==tk  | ==tk  | ==tk |
s5 |  =>tk  |  =>tk  |  =>tk   | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk  | =>tk |
s6 |  =<tk  |  =<tk  |  =<tk   | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk  | =<tk |
s7 |  <tk   |  <tk   |  <tk    | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk   | <tk  |
s8 |  s9    |  :tk   |  :tk    | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk   | :tk  |
s9 |  :=tk  |  :=tk  |  :=tk   | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk  | :=tk |
s10|  +tk   |  +tk   |  +tk    | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk   | +tk  |
s11|  -tk   |  -tk   |  -tk    | -tk   | -tk   | -tk   | -tk   | -tk   | +tk   | -tk   | -tk   | -tk   | -tk   | -tk   | -tk   | -tk   | -tk   | -tk   | -tk   | -tk   | -tk  |
s12|  *tk   |  *tk   |  *tk    | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk   | *tk  |
s13|  /tk   |  /tk   |  /tk    | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk   | /tk  |
s14|  %tk   |  %tk   |  %tk    | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk   | %tk  | 
s15|  .tk   |  .tk   |  .tk    | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk   | .tk  |
s16|  (tk   |  (tk   |  (tk    | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk   | (tk  |
s17|  )tk   |  )tk   |  )tk    | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk   | )tk  |
s18|  ,tk   |  ,tk   |  ,tk    | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk   | ,tk  |
s19|  {tk   |  {tk   |  {tk    | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk   | {tk  |
s20|  }tk   |  }tk   |  }tk    | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk   | }tk  |
s21|  ;tk   |  ;tk   |  ;tk    | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk   | ;tk  |
s22|  [tk   |  [tk   |  [tk    | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk   | [tk  |
s23|  ]tk   |  ]tk   |  ]tk    | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk   | ]tk  |
s24|  idtk  |  idtk  |  idtk   | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | idtk  | s24   | s24  |
s25|  inttk |  inttk |  inttk  | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | inttk | s25  |
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 

*/

//State table for construction of tokens.
stateT table[25][21] =
{
	{S2, S3, S7, S8, S10, S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, S21, S22, S23, S1, S24, S25},
	{S4, S5, S6, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{S9, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, S24, S24},
	{FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, S25}
};

#endif
