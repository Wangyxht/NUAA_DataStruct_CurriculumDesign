#ifndef BUS_H_
#define BUS_H_

#include"GraphList.hpp"
#include"LinkQueue.hpp"
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<vector>
#include<algorithm>
#include<deque>
#include<map>
#include<set>
#include<cstdlib>

#define MAX_BUS_NUM 990

//线路数据类型
struct route {
	int trans = 0;
	int station = 0;
	vector<string> path;
	vector<int> bus;

	void Show();
	void FileShow(ofstream& file);
};
//站点数据类型
struct stationInf {
	bool is_Trans = false;
	vector<int> buses;
	string name;
};
//换乘站车站队列基本类型
struct BusStationSearchInf {
	int bus=-1;
	int preStationLoc=-1;
	bool visit=false;
};

//菜单、操作界面
char Menu();
void SearchMenu();
void ShowRouteMenu(route r1, route r2);
void WriteFileRoute(ofstream& file ,route r1, route r2);

//站名合法性
bool StationNameValid(string start,string end, GraphList<string, int>& stationGraph);
//载入公交线路信息
status CreateStationGraph(std::ifstream& fileInput, GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus);
//利用站-车交通图构建车-站交通图
status CreateBusGraph(std::ifstream& fileInput, GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus);
//找寻最少换乘线路
route FindRouteLeastTrans(GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus, string startStation, string endStation);
//找寻经过站点最少线路
route FindRouteLeastStation(GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus, string startStation, string endStation);
//创建换乘简短路径
route CreatRouteLeastTrans(GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus, vector<BusStationSearchInf> visit_leastTrans, int startLoc, int endLoc);




#endif // !BUS_H_


