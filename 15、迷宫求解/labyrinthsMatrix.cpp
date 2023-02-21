#include "labyrinthsMatrix.h"
#include <iostream>
#include <set>
#include <Windows.h>
#include"sqStack.hpp"

std::vector<pair<int, int>> labyrinthsMatrix::FindPath(std::pair<int, int> start, std::pair<int, int> end)
{
	path.clear();
	if (start.first<1 || start.first>row) {
		return{};
	}
	
	if (start.second<1 || start.second>col) {
		return{};
	}

	path.clear();
	sqStack<pair<int, int>> stack;
	std::set<pair<int, int>> visited;
	stack.Push(start);
	visited.emplace(start);

	while (stack.GetTop() != end) {
		pair<int, int> cur_Loc = stack.GetTop();
		pair<int, int> cur_left(cur_Loc.first, cur_Loc.second + 1);
		pair<int, int> cur_right(cur_Loc.first, cur_Loc.second - 1);
		pair<int, int> cur_up(cur_Loc.first - 1, cur_Loc.second);
		pair<int, int> cur_down(cur_Loc.first + 1, cur_Loc.second);
		
		if (!IsWall(cur_left) && visited.find(cur_left) == visited.end()) {
			visited.emplace(cur_left);
			stack.Push(cur_left);
			continue;
		}
		else if (!IsWall(cur_right) && visited.find(cur_right) == visited.end()) {
			visited.emplace(cur_right);
			stack.Push(cur_right);
			continue;
		}
		else if (!IsWall(cur_up) && visited.find(cur_up) == visited.end()) {
			visited.emplace(cur_up);
			stack.Push(cur_up);
			continue;
		}
		else if (!IsWall(cur_down) && visited.find(cur_down) == visited.end()) {
			visited.emplace(cur_down);
			stack.Push(cur_down);
			continue;
		}
		else {
			stack.Pop();
		}
	}

	while (!stack.StackEmpty()) {
		std::pair<int, int> cur_Loc;
		stack.Pop(cur_Loc);
		path.emplace_back(cur_Loc);
	}

	std::reverse(path.begin(), path.end());
	return path;
}

int labyrinthsMatrix::IsWall(std::pair<int, int> loc)
{
	return Matrix[loc.first][loc.second];
}

void labyrinthsMatrix::ShowLabyrinths()
{
	std::cout << "  ";
	for (int i = 0; i <= col+1; ++i) {
		if (i < 10) {
			std::cout << i <<" ";
		}
		else {
			std::cout << i;
		}

	}
	std::cout << "\n";
	for (int i = 0; i < Matrix.size(); i++) {
		if (i < 10) {
			std::cout << i << " ";
		}
		else {
			std::cout << i;
		}
		for (int j = 0; j < Matrix[i].size(); j++) {
			if (Matrix[i][j]) std::cout << "¡õ";
			else std::cout << "  ";
		}
		
		std::cout << "\n";
	}
}

void labyrinthsMatrix::ShowPath()
{
	system("cls");
	for (int pathLoc = 0; pathLoc < path.size(); pathLoc++) {
		std::cout << "  ";
		for (int i = 0; i <= col + 1; ++i) {
			if (i < 10) {
				std::cout << i << " ";
			}
			else {
				std::cout << i;
			}

		}
		std::cout << "\n";
		for (int i = 0; i < Matrix.size(); i++) {
			if (i < 10) {
				std::cout << i << " ";
			}
			else {
				std::cout << i;
			}
			for (int j = 0; j < Matrix[i].size(); j++) {
				if (i == path[pathLoc].first && j == path[pathLoc].second) std::cout << "¡ï";
				else if(Matrix[i][j]) std::cout << "¡õ";
				else std::cout << "  ";
			}

			std::cout << "\n";
			
		}
		Sleep(10);
		system("cls");
	}

}
