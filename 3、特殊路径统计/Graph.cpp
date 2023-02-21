#include"SpecialPath.h"

void DFS_FindPath(GraphMat<int>& graph, vector<vector<int>>& pathList, int start, vector<int>& cur_path)
{
	graph.visit[start] = true;
	for (int w = graph.FirstAdjVex(start); w >= 0; w = graph.NextAdjVex(start, w)) {
		vector<int> path = cur_path;

		if (graph.visit[w] == false) {
			path.push_back(graph.GetVex(w));
			pathList.push_back(path);
			DFS_FindPath(graph, pathList, w, path);
		}


	}

	return;
}

std::vector<vector<vector<int>>> SearchAllPath(GraphMat<int>& graph)
{
	vector<vector<vector<int>>> allPath;
	
	for (int i = 1; i <= graph.VexNum(); ++i) {
		vector<vector<int>> cur_pathList;
		vector<int> path;
		path.push_back(i);
		graph.visit.assign(graph.visit.size(), false);
		DFS_FindPath(graph, cur_pathList, graph.LocateVex(i), path);
		allPath.push_back(cur_pathList);

	}

	return allPath;
}