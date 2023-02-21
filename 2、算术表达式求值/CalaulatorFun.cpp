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
		std::cout << "���벻������ѧ���ʽ\n";
		return false;
	}
	
	if ( expression[expression.size() - 1] == '+' || expression[expression.size() - 1] == '-'
		|| expression[expression.size() - 1] == '*' || expression[expression.size() - 1] == '/') {
		std::cout << "���벻������ѧ���ʽ\n";
		return false;
	}
	
	for (int i = 0; i < expression.length() - 1; ++i) {
		if (CharValid(expression[i],expression[i+1]) == false) {
			std::cout << "���벻������ѧ���ʽ\n";
			return false;
		}
	}

	if (BracketMatch(expression)==false) {
		std::cout << "���Ŵ���\n";
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
		if (ispunct(expression[i])) {//���Ϊһ�����ţ�С������⣩
			if (stackSign.StackEmpty()) {//���ջ��
				stackSign.Push(expression[i]);
				std::cout << "����ջ:";
				stackSign.StackTraverse();
				++i;
			}
			else {
				int condition = JudgeSignPriority(expression[i], stackSign.GetTop());
				if (condition == -1) {//�·������ȼ���
					stackSign.Push(expression[i]);
					std::cout << "����ջ:";
					stackSign.StackTraverse();
					++i;
				}
				else if (condition == 1) {//ջ���������ȼ���
					while (condition == 1) {
						PolishNotationElement cur_sign;
						cur_sign.isSign = true;
						stackSign.Pop(cur_sign.sign);
						std::cout << "����ջ:";
						stackSign.StackTraverse();
						PolishNotation.push_back(cur_sign);
						condition = JudgeSignPriority(expression[i], stackSign.GetTop());
						
					}
				}
				else if (condition == 0) {//���ȼ�һ��
					stackSign.Pop();
					std::cout << "����ջ:";
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
			std::cout << "�������ʽ:";
			for (int k = 0; k < PolishNotation.size(); ++k) {
				std::cout << PolishNotation[k] <<" ";
			}
			std::cout << "\n";
			i = j;
		}
	}

	std::cout << "\n�������ʽ:";
	for (int k = 0; k < PolishNotation.size(); ++k) {
		std::cout << PolishNotation[k] << " ";
	}
	std::cout << "\n";

	//����ջ���ò������ʽ���м���
	sqStack<PolishNotationElement> stackCalculate;
	i = 0;
	while (i < PolishNotation.size()) {
		if (PolishNotation[i].isNum) {
			stackCalculate.Push(PolishNotation[i]);
			std::cout << "���㣨��ֵ��ջ:";
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
				std::cout << "���㣨��ֵ��ջ:";
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
				std::cout << "���㣨��ֵ��ջ:";
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
				std::cout << "���㣨��ֵ��ջ:";
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
				std::cout << "���㣨��ֵ��ջ:";
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
