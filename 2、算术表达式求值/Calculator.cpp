#include"Calculator.h"

int main(int argc, char* argv[]) {
	std::ifstream fileIn("expressions.txt", std::ios::in);
	std::ofstream fileOut("answers.txt", std::ios::out | std::ios::trunc);
	
	if (fileIn.fail()) {
		throw"File cannot open.";
		fileIn.close();
		fileOut.close();
		exit(EXIT_FAILURE);
	}

	std::vector<std::string> expressions = ReadExpressions(fileIn);

	for (int i = 0; i < expressions.size(); ++i) {
		std::cout << "\n\n------------\n\n";
		if (ExpressionValid(expressions[i])) {
			
			fileOut << CalaulateExpression(expressions[i])<<'\n';
		}
		else {
			fileOut << "Invalid Expression\n";
		}
	}
	std::cout << "\n\n------------\n\n";

	fileIn.close();
	fileOut.close();
	return EXIT_SUCCESS;
}