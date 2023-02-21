#include<iostream>
#include<fstream>
#include"Bus.h"



int main(int argc, char** argv) {


	std::ifstream fileIn("南京公交线路.txt", std::ios::in);
	std::ofstream fileOut("线路查询结果.txt", std::ios::out | std::ios::trunc);


	if (fileIn.fail() || fileOut.fail()) {
		std::cout << "File cannot open." << std::endl;
		exit(EXIT_FAILURE);
	}

	GraphList<std::string, int> busStationGraph_NanJing;
	GraphList<int, stationInf> busGraph_NanJing;

	CreateStationGraph(fileIn, busStationGraph_NanJing,busGraph_NanJing);
	CreateBusGraph(fileIn,busStationGraph_NanJing,busGraph_NanJing);

	do {
		std::string start, destination;
		switch (Menu()) {
		
		case'q':
			exit(EXIT_SUCCESS);
			break;
		case'1':
			system("cls");
			do {
				SearchMenu();
				cin >> start >> destination;
				fflush(stdin);

				
				if (!StationNameValid(start,destination,busStationGraph_NanJing)) {
					system("cls");
					continue;
				}
				else {
					system("cls");
					route leastStationR = FindRouteLeastStation(busStationGraph_NanJing, busGraph_NanJing, start, destination);
					route leastTransR = FindRouteLeastTrans(busStationGraph_NanJing, busGraph_NanJing, start, destination);
					ShowRouteMenu(leastStationR, leastTransR);
					WriteFileRoute(fileOut, leastStationR, leastTransR);

				}

				system("cls");
				break;			
			} while (true);
			break;
		default:
			system("cls");
			break;
		}

	} while (true);

	
	return EXIT_SUCCESS;
}


