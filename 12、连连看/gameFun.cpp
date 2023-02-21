#include"game.h"

GamePlayTable::GamePlayTable()
{
	std::vector<int> cubeCount(MAX_CUBE_KIND+1, 0);
	std::default_random_engine dre(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<int> dr(1, 10);

	//随机创建方格
	for (int i = 0; i <= row + 1; ++i) {
		for (int j = 0; j <= col + 1; ++j) {
			if (i == 0 || j == 0 || i == row + 1 || j == col + 1) {
				table[i][j] = 0;
			}
			else {
				table[i][j] = dr(dre);
				cubeCount[table[i][j]]++;
			}

		}
	}

	//方块为奇数的颜色修正
	int exchangeCube1, exchangeCube2;
	do {
		exchangeCube1 = 0;
		exchangeCube2 = 0;
		for (int i = 1; i <= MAX_CUBE_KIND; ++i) {
			if (cubeCount[i] % 2 != 0) {
				exchangeCube1 = i;
				break;
			}
		}
		for (int i = exchangeCube1 + 1; i <= MAX_CUBE_KIND; ++i) {
			if (cubeCount[i] % 2 != 0) {
				exchangeCube2 = i;
				break;
			}
		}
		if (exchangeCube1 != 0 && exchangeCube2 != 0) {
			std::pair<int, int> coordinate1, coordinate2;
			for (int i = 0; i <= row; ++i) {
				for (int j = 0; j <= col; ++j) {
					if (table[i][j] == exchangeCube1) {
						coordinate1.first = i;
						coordinate1.second = j;
					}
				}
			}
			for (int i = 0; i <= row; ++i) {
				for (int j = 0; j <= col; ++j) {
					if (table[i][j] == exchangeCube2) {
						coordinate2.first = i;
						coordinate2.second = j;
					}
				}
			}
			table[coordinate1.first][coordinate1.second] = table[coordinate2.first][coordinate2.second];
			cubeCount[exchangeCube1]--;
			cubeCount[exchangeCube2]++;
		}


	} while (exchangeCube1 != 0 && exchangeCube2 != 0);
}

void GamePlayTable::DisplayGameTable()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 1; i <= row; ++i) {
		if (i == 1) {
			std::cout << "  ";
			for (int j = 1; j <= col; ++j) {

				if (j < 10) {
					std::cout << j << " ";
				}
				else {
					std::cout << j;
				}

			}
			std::cout << "\n";
		}

		for (int j = 1; j <= col; ++j) {
			if (j == 1) {
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
				if (i < 10) {
					std::cout << i << " ";
				}
				else {
					std::cout << i;
				}
			}

			switch (table[i][j]) {
			case 0:
				std::cout << "  ";
				break;
			case 1:
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
				std::cout << "■";
				break;
			case 2:
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
				std::cout << "■";
				break;
			case 3:
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "■";
				break;
			case 4:
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "■";
				break;
			case 5:
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED);
				std::cout << "■";
				break;
			case 6:
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << "■";;
				break;
			case 7:
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN);
				std::cout << "■";
				break;
			case 8:
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << "■";
				break;
			case 9:
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "■";
				break;
			case 10:
				SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << "■";
				break;

			}

		}
		std::cout << "\n";
	}
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	std::cout << "\n输入两个坐标位置来消除方块（纵坐标在前，横坐标在后）：\n";
}

bool GamePlayTable::Empty()
{
	return cubeNum == 0;
}

bool GamePlayTable::CoordinateValid(int x, int y)
{
	if (x <= 0 || x > row) {
		return false;
	}
	else if (y <= 0 || y > col) {
		return false;
	}
	return true;
}

bool GamePlayTable::CoordinateEmpty(int x, int y)
{
	return table[x][y] == 0;
}

bool GamePlayTable::CoordinateMatch(int x1, int y1, int x2, int y2)
{
	if (!CoordinateValid(x1, y1) || !CoordinateValid(x2, y2)) {//坐标不合法
		return false;
	}
	else if (table[x1][y1] != table[x2][y2]) {//颜色不符
		return false;
	}
	else if (x1 == x2 && y1 == y2) {//坐标重复
		return false;
	}

	return CoordinateMatchOneLine(x1, y1, x2, y2) || CoordinateMatchTwoLine(x1, y1, x2, y2) || CoordinateMatchThreeLine(x1, y1, x2, y2);
}

bool GamePlayTable::CoordinateMatchOneLine(int x1, int y1, int x2, int y2)
{
	if (x1 == x2) {
		for (int i = min(y1, y2) + 1; i < max(y1, y2); ++i) {
			if (!CoordinateEmpty(x1, i)) {
				return false;
			}
		}
	}
	else if (y1 == y2) {
		for (int i = min(x1, x2) + 1; i < max(x1, x2); ++i) {
			if (!CoordinateEmpty(i, y1)) {
				return false;
			}
		}
	}
	else {
		return false;
	}

	return true;
}

bool GamePlayTable::CoordinateMatchTwoLine(int x1, int y1, int x2, int y2)
{
	//检测先y后x路线
	int yi = y1;
	while (yi != y2) {
		if (y1 > y2) --yi;
		else if (y1 < y2) ++yi;

		if (!CoordinateEmpty(x1, yi)) break;
		
		if (yi == y2) {
			if (CoordinateMatchOneLine(x1, yi, x2, y2)) return true;
			else break;
		}
	}

	//检测先x后y路线
	int xi = x1;
	while (xi != x2) {
		if (x1 > x2) --xi;
		else if (x1 < x2) ++xi;

		if (!CoordinateEmpty(xi, y1)) return false;

		if (xi == x2) {
			if (CoordinateMatchOneLine(xi, y1, x2, y2)) return true;
			else return false;
		}
	}

	return false;
}

bool GamePlayTable::CoordinateMatchThreeLine(int x1, int y1, int x2, int y2)
{
	int yi = y1;
	while (yi >=0) {
		 --yi;
		if (!CoordinateEmpty(x1, yi)) break;
		if (CoordinateMatchTwoLine(x1, yi, x2, y2)) return true;
	}
	yi = y1;
	while (yi <= col + 1) {
		++yi;
		if (!CoordinateEmpty(x1, yi)) break;
		if (CoordinateMatchTwoLine(x1, yi, x2, y2)) return true;
	}

	int xi = x1;
	while (xi >= 0) {
		--xi;
		if (!CoordinateEmpty(xi, y1)) break;
		if (CoordinateMatchTwoLine(xi, y1, x2, y2)) return true;
	}
	xi = x1;
	while (xi <= row + 1) {
		++xi;
		if (!CoordinateEmpty(xi, y1)) break;
		if (CoordinateMatchTwoLine(xi, y1, x2, y2)) return true;
	}
	return false;
}

void GamePlayTable::DestoryCoordinate(int x, int y)
{
	table[x][y] = 0;
	--cubeNum;
}
