#include"Calculator.h"

std::ostream& operator<<(std::ostream& os, const PolishNotationElement& element)
{
	if (element.isNum) {
		os << element.num << " ";
	}
	else if (element.isSign) {
		os << element.sign << " ";
	}

	return os;
}

std::vector<std::string> ReadExpressions(std::ifstream& fileIn)
{
	std::vector<std::string> expressuionsList;
	while (fileIn.eof() == false) {
		std::string expressions;
		getline(fileIn,expressions);
		expressuionsList.push_back(expressions);
	}

	return expressuionsList;
}

bool ExpressionValid(std::string expression)
{
	if (expression[0] == '+' || expression[0] == '-' || expression[0] == '*' || expression[0] == '/') {
		std::cout << "输入不符合数学表达式\n";
		return false;
	}
	
	if ( expression[expression.size() - 1] == '+' || expression[expression.size() - 1] == '-'
		|| expression[expression.size() - 1] == '*' || expression[expression.size() - 1] == '/') {
		std::cout << "输入不符合数学表达式\n";
		return false;
	}
	
	for (int i = 0; i < expression.length() - 1; ++i) {
		if (CharValid(expression[i],expression[i+1]) == false) {
			std::cout << "输入不符合数学表达式\n";
			return false;
		}
	}

	if (BracketMatch(expression)==false) {
		std::cout << "括号错误\n";
		return false;
	}
	
	return true;
}

bool CharValid(char ch)
{
	if (isdigit(ch) == false && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '.' && ch != '(' && ch != ')') {
		return false;
	}

	return true;
}

bool CharValid(char pre_char, char next_char)
{
	if (CharValid(pre_char) && CharValid(next_char)) {
		if (pre_char == '+' || pre_char == '-' || pre_char == '*' || pre_char == '/' || pre_char == '.' || pre_char == '(') {
			if (next_char == '+' || next_char == '-' || next_char == '*' || next_char == '/' || next_char == '.' || pre_char == ')') {
				return false;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

bool BracketMatch(std::string expression)
{
	sqStack<char> stack;
	for (int i = 0; i < expression.length(); ++i) {
		if (expression[i] == '(') {
			stack.Push(expression[i]);
		}
		else if (expression[i] == ')') {
			if (stack.GetTop() != '('){
				return false;
			}
			else {
				stack.Pop();
			}
		}
	}

	if (stack.StackEmpty()) {
		return true;
	}
	else {
		return false;
	}
}

float CalaulateExpression(std::string expression)
{
	sqStack<char> stackSign;
	std::vector<PolishNotationElement> PolishNotation;
	
	expression.insert(expression.begin(), '#');
	expression.insert(expression.end(), '#');

	int i = 0;
	while(i < expression.size()) {
		if (ispunct(expression[i])) {//如果为一个符号（小数点除外）
			if (stackSign.StackEmpty()) {//如果栈空
				stackSign.Push(expression[i]);
				std::cout << "符号栈:";
				stackSign.StackTraverse();
				++i;
			}
			else {
				int condition = JudgeSignPriority(expression[i], stackSign.GetTop());
				if (condition == -1) {//新符号优先级高
					stackSign.Push(expression[i]);
					std::cout << "符号栈:";
					stackSign.StackTraverse();
					++i;
				}
				else if (condition == 1) {//栈顶符号优先级高
					while (condition == 1) {
						PolishNotationElement cur_sign;
						cur_sign.isSign = true;
						stackSign.Pop(cur_sign.sign);
						std::cout << "符号栈:";
						stackSign.StackTraverse();
						PolishNotation.push_back(cur_sign);
						condition = JudgeSignPriority(expression[i], stackSign.GetTop());
						
					}
				}
				else if (condition == 0) {//优先级一致
					stackSign.Pop();
					std::cout << "符号栈:";
					stackSign.StackTraverse();
					++i;
				}
			}
		}
		else if (isdigit(expression[i])) {
			int j = i;
			while(ispunct(expression[j])==false || expression[j]=='.') {
				++j;
			}
			std::string cur_numStr(expression, i, j - 1);
			float cur_numf = std::stof(cur_numStr);
			PolishNotationElement cur_num;
			cur_num.isNum = true;
			cur_num.num = cur_numf;
			PolishNotation.push_back(cur_num);
			std::cout << "波兰表达式:";
			for (int k = 0; k < PolishNotation.size(); ++k) {
				std::cout << PolishNotation[k] <<" ";
			}
			std::cout << "\n";
			i = j;
		}
	}

	std::cout << "\n波兰表达式:";
	for (int k = 0; k < PolishNotation.size(); ++k) {
		std::cout << PolishNotation[k] << " ";
	}
	std::cout << "\n";

	//计算栈利用波兰表达式进行计算
	sqStack<PolishNotationElement> stackCalculate;
	i = 0;
	while (i < PolishNotation.size()) {
		if (PolishNotation[i].isNum) {
			stackCalculate.Push(PolishNotation[i]);
			std::cout << "计算（数值）栈:";
			stackCalculate.StackTraverse();
			++i;
		}
		else if (PolishNotation[i].isSign) {
			PolishNotationElement numA, numB;
			switch (PolishNotation[i].sign) {
			case'+': {
				stackCalculate.Pop(numA);
				stackCalculate.Pop(numB);
				PolishNotationElement numCalaulate;
				numCalaulate.isNum = true;
				numCalaulate.num = numA.num + numB.num;
				stackCalculate.Push(numCalaulate);
				std::cout << "计算（数值）栈:";
				stackCalculate.StackTraverse();
				break;
			}
			case'-': {
				stackCalculate.Pop(numA);
				stackCalculate.Pop(numB);
				PolishNotationElement numCalaulate;
				numCalaulate.isNum = true;
				numCalaulate.num = numB.num - numA.num;
				stackCalculate.Push(numCalaulate);
				std::cout << "计算（数值）栈:";
				stackCalculate.StackTraverse();

				break;
			}

			case '*': {
				stackCalculate.Pop(numA);
				stackCalculate.Pop(numB);
				PolishNotationElement numCalaulate;
				numCalaulate.isNum = true;
				numCalaulate.num = numA.num * numB.num;
				stackCalculate.Push(numCalaulate);
				std::cout << "计算（数值）栈:";
				stackCalculate.StackTraverse();
				break;
			}
			case '/': {
				stackCalculate.Pop(numA);
				stackCalculate.Pop(numB);
				PolishNotationElement numCalaulate;
				numCalaulate.isNum = true;
				numCalaulate.num = numB.num / numA.num;
				stackCalculate.Push(numCalaulate);
				std::cout << "计算（数值）栈:";
				stackCalculate.StackTraverse();
				break;
			}
			default: {
				break;
			}
			}
			++i;
		}
	}

	return stackCalculate.GetTop().num;
}

int JudgeSignPriority(char sign_next, char sign_former)
{
	int i, j;
	for (i = 1; i < 8; i++) {
		if (sign_next == PriorityList[0][i]) {
			break;
		}
	}
	for (j = 1; j < 8; j++) {
		if (sign_former == PriorityList[j][0]) {
			break;
		}
	}

	return PriorityList[j][i];
}
