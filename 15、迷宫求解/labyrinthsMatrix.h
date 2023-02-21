#pragma once
#include<vector>
class labyrinthsMatrix
{
private:
	std::vector<std::vector<int>> Matrix;
	std::vector<std::pair<int, int>> path;
	int row;
	int col;
	const int left = 1;
	const int right = -1;
	const int up = 2;
	const int down = -2;
	

public:
	labyrinthsMatrix(std::vector<std::vector<int>> Matrix,int row,int col) :Matrix(Matrix),row(row),col(col) {};
	std::vector<std::pair<int, int>> FindPath(std::pair<int, int> start, std::pair<int, int> end);
	int IsWall(std::pair<int, int> loc);
	void ShowLabyrinths();
	void ShowPath();
};
