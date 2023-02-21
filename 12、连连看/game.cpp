#include"game.h"

int main(int argc, char** argv) {

	GamePlayTable gameTable;

	std::cout << "开始游戏！\n\n";
	while (!gameTable.Empty()) {
		gameTable.DisplayGameTable();
		int x1, y1, x2, y2;
		std::cin >> x1 >> y1 >> x2 >> y2;
		system("cls");
		if (gameTable.CoordinateMatch(x1, y1, x2, y2)) {
			gameTable.DestoryCoordinate(x1, y1);
			gameTable.DestoryCoordinate(x2, y2);
			std::cout << "消去成功！\n\n";
		}
		else {
			std::cout << "两个坐标对应的方块无法消去！\n\n";
		}
	}

	std::cout << "YOU WIN\n\n";
	return EXIT_SUCCESS;
}
