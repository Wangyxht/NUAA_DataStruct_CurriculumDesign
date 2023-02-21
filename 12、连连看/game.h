#ifndef GAME_H_
#define GAME_H_

#include<iostream>
#include<random>
#include<cstdlib>
#include<Windows.h>
#include<ctime>
#include<algorithm>
#include<vector>

class GamePlayTable {
private:
	static const int row = 15;
	static const int col = 20;
	static const int MAX_CUBE_KIND = 10;
	int table[row + 2][col + 2];
	int cubeNum = row * col;
	bool CoordinateMatchOneLine(int x1, int y1, int x2, int y2);
	bool CoordinateMatchTwoLine(int x1, int y1, int x2, int y2);
	bool CoordinateMatchThreeLine(int x1, int y1, int x2, int y2);

public:
	GamePlayTable();//���캯�� ��������������	
	void DisplayGameTable();//��ʾ��Ϸ����
	bool Empty();//�ж������Ƿ�����
	bool CoordinateValid(int x, int y);//�ж������Ƿ�Ϸ�
	bool CoordinateEmpty(int x, int y);
	bool CoordinateMatch(int x1, int y1, int x2, int y2);
	void DestoryCoordinate(int x, int y);
	
};

#endif // !GAME_H_

