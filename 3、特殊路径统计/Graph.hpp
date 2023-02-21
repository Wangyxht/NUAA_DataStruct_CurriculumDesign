#ifndef GRAPH_HPP
#define GRAPH_HPP

#include<iostream>
#include<tuple>
#include<vector>
#include"SpecialPath.h"
#include"LinkQueue.hpp"

#define INFINITY INT_MAX
#define OK 1
using status = int;

template<class T>
class GraphMat{

private:
	vector<T> vexs;//顶点信息
	vector<vector<int>> arcs;//邻接矩阵

	int graphType;//图的种类
	size_t vexnum = 0;
	size_t arcnum = 0;

public:
	vector<bool> visit;

	GraphMat() :vexs({}), arcs({}), visit({}), graphType(-1) {};//构造函数,未使用new则自动析构（destory）
	//Graph(const Graph<T>& graph);
	//Graph<T>& operator=(const Graph<T>& graph);

	status CreatGraph();//创建邻接矩阵
	int VexNum();
	int LocateVex(T vexData);//定位节点编号
	T GetVex(int vex) const;//访问节点值
	int FirstAdjVex(int vex);//返回节点第一条边
	int NextAdjVex(int vex, int w);//返回下一条边
	status ShowMat();
	status DFSTraverse();//DFS遍历
	status DFS(int vex);//DFS
	status BFSTraverse();//BFS遍历
	status BFS(int vex);//BFS
	status InsertVex(T vexData);
	status InsertArc(T vexDataStart, T vexDataEnd);
	status InsertArc(T vexDataStart, T vexDataEnd, int weight);
	status DeleteVex(T vexData);
	status DeleteArc(T vexDataStart, T vexDataEnd);

	friend std::vector<vector<vector<int>>> SearchAllPath(GraphMat<int>& graph);
	friend void DFS_FindPath(GraphMat<int>& graph, vector<vector<int>>& pathList,int start, vector<int>& cur_path);
};



template<class T>
status GraphMat<T>::CreatGraph()
{
	try {
		graphType = 0;
		std::cout << "输入顶点个数：";
		std::cin >> vexnum;
		vexs.assign(vexnum, {});
		visit.assign(vexnum, false);
		
		arcs.assign(vexnum, {});
		for (int i = 0; i < vexnum; ++i) {
			arcs[i].assign(vexnum, 0);
			vexs[i] = i + 1;
		}

		std::cout << "按顺序输入父节点：" << endl;
		for (int i = 0; i < vexnum; ++i) {
			T parent;
			std::cin >> parent;
			if (parent == 0) continue;
			arcs[LocateVex(parent)][LocateVex(i + 1)] = 1;
			arcs[LocateVex(i + 1)][LocateVex(parent)] = 1;
		}

	}
	catch (bad_alloc& e) {
		cout << e.what();
		exit(OVERFLOW);
	}

	return OK;
}

template<class T>
int GraphMat<T>::VexNum()
{
	return vexnum;
}

template<class T>
int GraphMat<T>::LocateVex(T vexData)
{
	if (graphType == -1) throw "graphEmpty";

	for (int i = 0; i < vexnum; ++i) {
		if (vexData == vexs[i]) {
			return i;
		}
	}

	return -1;
}

template<class T>
T GraphMat<T>::GetVex(int vex) const
{
	if (graphType == -1) throw "graphEmpty";
	return vexs[vex];
}

template<class T>
int GraphMat<T>::FirstAdjVex(int vex)
{
	if (graphType == -1) throw "graphEmpty";
	for (int i = vex, j = 0; j < vexnum; ++j) {
		if (graphType == 1 || graphType == 0) {
			if (arcs[i][j] != 0) return j;
		}
		else {
			if (arcs[i][j] != INFINITY) return j;
		}
	}

	return -1;
}

template<class T>
int GraphMat<T>::NextAdjVex(int vex, int w)
{
	if (graphType == -1) throw "graphEmpty";
	for (int i = vex, j = w + 1; j < vexnum; ++j) {
		if (graphType == 1 || graphType == 0) {
			if (arcs[i][j] != 0) return j;
		}
		else {
			if (arcs[i][j] != INFINITY) return j;
		}
	}

	return -1;
}

template<class T>
status GraphMat<T>::ShowMat()
{
	for (int i = 0; i < vexnum; ++i) {
		for (int j = 0; j < vexnum; ++j) {
			if (arcs[i][j] != INFINITY) {
				std::cout << right << arcs[i][j] << ' ';
			}
			else {
				std::cout << "∞" << ' ';
			}

		}
		cout << endl;
	}

	return OK;
}

template<class T>
status GraphMat<T>::DFSTraverse()
{
	visit.assign(vexnum, false);
	if (graphType == -1) return false;
	for (int i = 0; i < vexnum; ++i) {
		if (visit[i] == false) DFS(i);
	}
	return OK;
}

template<class T>
status GraphMat<T>::DFS(int vex)
{
	visit[vex] = true;
	cout << vexs[vex];
	for (int w = FirstAdjVex(vex); w >= 0; w = NextAdjVex(vex, w)) {
		if (visit[w] == false) DFS(w);
	}

	return OK;

}

template<class T>
status GraphMat<T>::BFSTraverse()
{
	visit.assign(vexnum, false);
	if (graphType == -1) return false;
	for (int i = 0; i < vexnum; ++i) {
		if (visit[i] == false) BFS(i);
	}
	return OK;
}

template<class T>
status GraphMat<T>::BFS(int vex)
{
	LinkQueue<int> queue;
	queue.EnQueue(vex);
	cout << vexs[vex];
	visit[vex] = true;
	while (queue.QueueEmpty() == false) {
		int t;
		queue.DeQueue(t);
		for (int j = 0; j < vexnum; ++j) {
			if (graphType == 0 || graphType == 1) {
				if (arcs[t][j] == 1 && visit[j] == false) {
					queue.EnQueue(j);
					visit[j] = true;
					cout << vexs[j];
				}
			}
			else {
				if (arcs[t][j] != INFINITY && visit[j] == false) {
					queue.EnQueue(j);
					visit[j] = true;
					cout << vexs[j];
				}
			}
		}
	}

	return OK;
}

template<class T>
status GraphMat<T>::InsertVex(T vexData)
{

	vexs.push_back(vexData);
	++vexnum;
	arcs.push_back({});
	visit.push_back(false);

	if (graphType == 1 || graphType == 0) {
		arcs[vexnum - 1].assign(vexnum, 0);
		for (int i = 0; i < vexnum - 1; ++i) {
			arcs[i].push_back(0);
		}

	}
	else {
		arcs[vexnum - 1].assign(vexnum, INFINITY);
		for (int i = 0; i < vexnum - 1; ++i) {
			arcs[i].push_back(INFINITY);
		}
	}
	return OK;
}

template<class T>
status GraphMat<T>::InsertArc(T vexDataStart, T vexDataEnd)
{
	if (graphType == -1 || graphType == 2 || graphType == 3) return false;
	int startLoc = LocateVex(vexDataStart);
	int endLoc = LocateVex(vexDataEnd);
	if (startLoc == -1 || endLoc == -1) return false;

	if (graphType == 0) {
		arcs[startLoc][endLoc] = 1;
		arcs[endLoc][startLoc] = 1;
	}
	else {
		arcs[startLoc][endLoc] = 1;
	}
	++arcnum;
	return OK;
}

template<class T>
status GraphMat<T>::InsertArc(T vexDataStart, T vexDataEnd, int weight)
{
	if (graphType == -1 || graphType == 0 || graphType == 1) return false;
	int startLoc = LocateVex(vexDataStart);
	int endLoc = LocateVex(vexDataEnd);
	if (startLoc == -1 || endLoc == -1) return false;

	if (graphType == 2) {
		arcs[startLoc][endLoc] = weight;
		arcs[endLoc][startLoc] = weight;
	}
	else {
		arcs[startLoc][endLoc] = weight;
	}
	++arcnum;
	return OK;
}

template<class T>
status GraphMat<T>::DeleteVex(T vexData)
{
	if (graphType == -1) return false;
	int vex = LocateVex(vexData);
	if (vex == -1) return false;

	for (int i = 0; i < vexnum; ++i) {
		arcs[i].erase(arcs[i].cbegin() + vex);
	}
	arcs.erase(arcs.cbegin() + vex);

	vexs.erase(vexs.cbegin() + vex);

	visit.erase(visit.cbegin() + vex);
	--vexnum;
	return OK;
}

template<class T>
status GraphMat<T>::DeleteArc(T vexDataStart, T vexDataEnd)
{
	if (graphType == -1) return false;
	int startLoc = LocateVex(vexDataStart);
	int endLoc = LocateVex(vexDataEnd);
	if (startLoc == -1 || endLoc == -1) return false;

	if (graphType == 0) {
		arcs[startLoc][endLoc] = 0;
		arcs[endLoc][startLoc] = 0;
	}
	else if (graphType == 1) {
		arcs[startLoc][endLoc] = 0;
	}
	else if (graphType == 2) {
		arcs[startLoc][endLoc] = INFINITY;
		arcs[endLoc][startLoc] = INFINITY;
	}
	else {
		arcs[startLoc][endLoc] = INFINITY;
	}

	--arcnum;
	return OK;



}



#endif // !GRAPH_HPP



