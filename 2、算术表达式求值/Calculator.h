#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include<iostream>
#include<cctype>
#include<vector>
#include<fstream>
#include<string>
#include"sqStack.hpp"

static const short PriorityList[8][8] =
{
	{ 0, '+','-','*','/','(',')','#'},
	{'+', 1,  1, -1, -1, -1,  1,  1 },
	{'-', 1,  1, -1, -1, -1,  1,  1 },
	{'*', 1,  1,  1,  1, -1,  1,  1 },
	{'/', 1,  1,  1,  1, -1,  1,  1 },
	{'(',-1, -1, -1, -1, -1,  0, -2 },
	{')', 1,  1,  1,  1, -2,  1,  1 },
	{'#',-1, -1, -1, -1, -1, -2,  0 }
}; 

struct PolishNotationElement {
	float num;
	char sign;
	bool isNum = false;
	bool isSign = false;

	friend std::ostream& operator<<(std::ostream& os,const PolishNotationElement& element);
};

std::vector<std::string> ReadExpressions(std::ifstream& fileIn);

bool ExpressionValid(std::string expression);

bool CharValid(char ch);

bool CharValid(char pre_char, char next_char);

bool BracketMatch(std::string expression);

float CalaulateExpression(std::string expression);

int JudgeSignPriority(char sign_next, char sign_former);



#endif // !CALCULATOR_H_

