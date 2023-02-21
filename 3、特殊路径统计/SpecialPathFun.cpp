#include"SpecialPath.h"

int CheckSpecialPath(const vector<vector<vector<int>>>& pathList)
{
	int num = 0;
	for (int i = 0; i < pathList.size(); ++i) {
		for (int j = 0; j < pathList[i].size(); ++j) {
			if (pathList[i][j].size() == 2) {
				if (pathList[i][j][0] < pathList[i][j][1]) {
					num++;
				}
				
			}
			else {
				bool correct = true;
				for (int k = 1; k < pathList[i][j].size() - 1; ++k) {
					
					if (pathList[i][j][k] > pathList[i][j][pathList[i][j].size() - 1] || pathList[i][j][k] < pathList[i][j][0]) {
						correct = false;
						break;
					}
				}
				if (correct) {
					num++;
				}
			}

		}
	}

	return num;
}