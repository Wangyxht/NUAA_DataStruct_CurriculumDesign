#include"game.h"

int main(int argc, char** argv) {

	GamePlayTable gameTable;

	std::cout << "��ʼ��Ϸ��\n\n";
	while (!gameTable.Empty()) {
		gameTable.DisplayGameTable();
		int x1, y1, x2, y2;
		std::cin >> x1 >> y1 >> x2 >> y2;
		system("cls");
		if (gameTable.CoordinateMatch(x1, y1, x2, y2)) {
			gameTable.DestoryCoordinate(x1, y1);
			gameTable.DestoryCoordinate(x2, y2);
			std::cout << "��ȥ�ɹ���\n\n";
		}
		else {
			std::cout << "���������Ӧ�ķ����޷���ȥ��\n\n";
		}
	}

	std::cout << "YOU WIN\n\n";
	return EXIT_SUCCESS;
}
