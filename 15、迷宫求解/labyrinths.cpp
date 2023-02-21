#include"labyrinths.h"

int main(int argc, char* argv[]) {
	std::ifstream fileIn("迷宫样例.txt", std::ios::in);
	if (fileIn.fail()) {
		throw "File cannot open";
		exit(EXIT_FAILURE);
	}

	labyrinthsMatrix labyrinths = LoadLabyrinthsMatrix(fileIn);
	

	while (true) {
		labyrinths.ShowLabyrinths();
		std::cout << "输入迷宫的起点与终点坐标:\n";
		std::pair<int, int> start;
		std::pair<int, int> end;
		std::cin >> start.first >> start.second;
		std::cin >> end.first >> end.second;
		fflush(stdin);

		labyrinths.FindPath(start, end);
		labyrinths.ShowPath();

		
	}

	fileIn.close();
	return EXIT_SUCCESS;

}

