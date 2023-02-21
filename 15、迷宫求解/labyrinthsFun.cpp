#include"labyrinths.h"

labyrinthsMatrix LoadLabyrinthsMatrix(std::ifstream& fileIn)
{
	int row, col;
	fileIn >> row >> col;

	std::vector<std::vector<int>> matrix;
	for (int i = 0; i <= row + 1; ++i) {
		std::vector<int> cur_row;
		if (i == 0 || i == row + 1) {
			cur_row.assign(col + 2 ,1);
			matrix.emplace_back(cur_row);
		}
		else {
			for (int j = 0; j <= col + 1; j++) {
				if (j == 0 || j == col + 1) {
					cur_row.emplace_back(1);
				}
				else {
					int block;
					fileIn >> block;
					cur_row.emplace_back(block);
				}
			}
			matrix.emplace_back(cur_row);
		}
	}
	labyrinthsMatrix labyrinths(matrix,row,col);
	return labyrinths;
}
