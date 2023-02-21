#include"Bus.h"

//ϵͳ���˵�
char Menu() {
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << "\n\t\t\t\t\t\t������·��ѯϵͳ\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t\t1�����ҳ˳�·��\t\t\t\tq)�˳�\n";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';

	char choice;
	cin >> choice;
	fflush(stdin);
	return choice;
}

void SearchMenu() {
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << "\n\t\t\t\t\t\t������·��ѯϵͳ\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t\t\t\t���������վ���յ�վ";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << "\n\t\t\t\t\t_______________________________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";


}

void WriteFileRoute(ofstream& file, route r1, route r2)
{
	file << '\n';
	file << '\n';
	file << '\n';
	file << '\n';
	file << '\n';
	file << "-------------------------------------------------------------------------------------------------";
	file << '\n';
	file << "��̳˳�·�ߣ�";
	r1.FileShow(file);
	file << '\n';
	file << '\n';
	file << "����" << r1.station << "��վ�㣬��Ҫ����" << r1.trans << "��\n";
	file << "-------------------------------------------------------------------------------------------------";
	file << '\n';
	file << "------------------------------------------------------------------------------------------------";
	file << '\n';
	file << "���ٻ���·�ߣ�";
	r2.FileShow(file);
	file << '\n';
	file << '\n';
	file << "����" << r2.station << "��վ�㣬��Ҫ����" << r2.trans << "��\n";
	file << "-------------------------------------------------------------------------------------------------";
	file << '\n';

}

void ShowRouteMenu(route r1, route r2)
{
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "-------------------------------------------------------------------------------------------------";
	cout << '\n';
	cout << "��̳˳�·�ߣ�";
	r1.Show();
	cout << '\n';
	cout << '\n';
	cout << "����" << r1.station << "��վ�㣬��Ҫ����" << r1.trans << "��\n";
	cout << "-------------------------------------------------------------------------------------------------";
	cout << '\n';
	cout << "------------------------------------------------------------------------------------------------";
	cout << '\n';
	cout << "���ٻ���·�ߣ�";
	r2.Show();
	cout << '\n';
	cout << '\n';
	cout << "����" << r2.station << "��վ�㣬��Ҫ����" << r2.trans << "��\n";
	cout << "-------------------------------------------------------------------------------------------------";
	cout << '\n';
	system("pause");
}

void route::Show()
{
	for (int i = 0; i < path.size(); ++i) {
		if (i == path.size() - 1) {
			cout << path[i];
		}
		else {
			cout << path[i] << "-----" << bus[i] << "----->";
		}
	}
	cout << '\n';
}

void route::FileShow(ofstream& file)
{


	for (int i = 0; i < path.size(); ++i) {
		if (i == path.size() - 1) {
			file << path[i];
		}
		else {
			file << path[i] << "-----" << bus[i] << "----->";
			if ((i + 1) % 10 == 0) file << '\n';
		}
	}
	file << '\n';

}

/***************************************************************
  *  @brief     �ж�վ���ĺϷ���
  *  @param     start�����վ end���յ�վ graph��վ-վͼ
  *  @note      ��ע
 **************************************************************/
bool StationNameValid(string start, string end, GraphList<string, int>& graph) {
	if (graph.LocateVex(start) == -1 || graph.LocateVex(end) == -1) return false;
	else return true;
}

/***************************************************************
  *  @brief     ����վ-վͼ
  *  @param     fileInput�� �����ļ� graphStation��վ-վͼ��Ӧ��Ϊ�գ� graphBus����-վͼ��Ӧ��Ϊ�գ�
  *  @note      ��ע
 **************************************************************/
status CreateStationGraph(std::ifstream& fileInput, GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus) {

	for (int line = 1; line < MAX_BUS_NUM; line++) {
		string busLine;
		getline(fileInput, busLine);

		bool is_BusName = true;
		bool is_StationName = false;
		string pre_Station;
		int busName = 0;
		int stationNum = 0;

		for (int i = 0; i < busLine.length(); ++i) {
			string station;
			if (is_BusName) {
				while (busLine[i + 2] != ' ') {
					busName = (busLine[i] - '0') + busName * 10;
					++i;
				}
				i += 4;
				is_BusName = false;
				is_StationName = true;
				graphBus.InsertVex(busName);
			}
			else if (busLine[i] == ',') {
				continue;
			}
			else if (busLine[i] == '\0') {
				break;
			}
			else if (is_StationName) {
				while (busLine[i] != ',' && busLine[i] != '\0') {
					station += busLine[i];
					i++;
				}

				if (graphStation.LocateVex(station) == -1) {
					graphStation.InsertVex(station);
				}
				stationNum++;
				if (stationNum >= 2) {
					graphStation.InsetArc(pre_Station, station, busName);
				}
				pre_Station = station;
			}
		}
	}

	return OK;
}

/***************************************************************
  *  @brief     ������-վͼ
  *  @param     fileInput�� �����ļ� graphStation��վ-վͼ��Ӧ��Ϊ�գ� graphBus����-վͼ��Ӧ��Ϊ�գ�
  *  @note      ��ע
 **************************************************************/
status CreateBusGraph(std::ifstream& fileInput, GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus)
{
	fileInput.close();
	fileInput.open("�Ͼ�������·.txt", std::ios::in);
	if (fileInput.fail()) {
		std::cout << "File cannot open." << std::endl;
		exit(EXIT_FAILURE);
	}

	string busLine;

	for (int line = 1; line < MAX_BUS_NUM; line++) {
		getline(fileInput, busLine);

		bool is_BusName = true;
		bool is_StationName = false;
		int busName = 0;
		int stationNum = 0;

		for (int i = 0; i < busLine.length(); ++i) {
			string station;
			if (is_BusName) {
				while (busLine[i + 2] != ' ') {
					busName = (busLine[i] - '0') + busName * 10;
					++i;
				}
				i += 4;
				is_BusName = false;
				is_StationName = true;
			}
			else if (busLine[i] == ',') {
				continue;
			}
			else if (busLine[i] == '\0') {
				break;
			}
			else if (is_StationName) {
				while (busLine[i] != ',' && busLine[i] != '\0') {
					station += busLine[i];
					i++;
				}

				int busLoc = graphBus.LocateVex(busName);
				int stationLoc = graphStation.LocateVex(station);
				stationInf stationInformation;
				stationInformation.name = station;

				if (graphStation.VexAdjVexNum(stationLoc) == 1) {
					stationInformation.is_Trans = false;
					stationInformation.buses.push_back(graphStation.FirstArc(stationLoc)->arcInf);
					ArcNode<stationInf>* p = graphBus.FirstArc(busLoc);
					if (p == nullptr) {
						p = graphBus.FirstArc(busLoc) = new ArcNode<stationInf>;
						p->preArc = nullptr;
						p->nextArc = nullptr;
						p->arcInf = stationInformation;
					}
					else {
						for (p = graphBus.FirstArc(busLoc); p->nextArc; p = graphBus.NextArc(busLoc, p));
						p->nextArc = new ArcNode<stationInf>;
						p->nextArc->preArc = p;
						p = p->nextArc;
						p->nextArc = nullptr;
						p->arcInf = stationInformation;

					}

				}
				else {

					stationInformation.is_Trans = true;
					for (auto p = graphStation.FirstArc(stationLoc); p->nextArc; p = graphStation.NextArc(stationLoc, p)) {
						if (find(stationInformation.buses.cbegin(), stationInformation.buses.cend(), p->arcInf) == stationInformation.buses.cend()) {
							stationInformation.buses.push_back(p->arcInf);
						}
					}
					ArcNode<stationInf>* p = graphBus.FirstArc(busLoc);
					if (p == nullptr) {
						p = graphBus.FirstArc(busLoc) = new ArcNode<stationInf>;
						p->preArc = nullptr;
						p->nextArc = nullptr;
						p->arcInf = stationInformation;
					}
					else {
						for (p = graphBus.FirstArc(busLoc); p->nextArc; p = graphBus.NextArc(busLoc, p));
						p->nextArc = new ArcNode<stationInf>;
						p->nextArc->preArc = p;
						p = p->nextArc;
						p->nextArc = nullptr;
						p->arcInf = stationInformation;
					}

				}


			}


		}
	}


	return OK;
}

/***************************************************************
  *  @brief     ����վ-վͼ�ҵ�һ����̵�·��
  *  @param     graphStation��վ-վͼ graphBus����-վͼ startStation�����վ endStation���յ�վ
  *  @note      ԭ�������������
 **************************************************************/
route FindRouteLeastStation(GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus, string startStation, string endStation) {
	int startLoc = graphStation.LocateVex(startStation);
	int endLoc = graphStation.LocateVex(endStation);
	graphStation.visit.assign(graphStation.visit.size(), INT_MAX);
	route LeastStationRoute;

	LinkQueue<int> queue;
	queue.EnQueue(startLoc);//���վ��������
	int vexLoc;
	graphStation.visit[startLoc] = false;
	while (queue.QueueEmpty() == false) {
		queue.DeQueue(vexLoc);

		if (vexLoc == endLoc) {//�ҵ��յ�վֹͣBFS
			break;
		}
		else {//�����յ�վ
			for (auto p = graphStation.FirstArc(vexLoc); p; p = graphStation.NextArc(vexLoc, p)) {
				if (graphStation.visit[p->adjvex] == INT_MAX) {//�����վ��ɴ����һվû�б����ʹ��������
					queue.EnQueue(p->adjvex);
				}
				graphStation.visit[p->adjvex] = min(graphStation.visit[p->adjvex], graphStation.visit[vexLoc] + 1);//��վ����һվ��ˢ��վ������ȡ��С��

			}
		}
	}

	LeastStationRoute.path.emplace_back(graphStation.GetVex(endLoc));
	while (vexLoc != startLoc) {//���ݣ����յ�վ��ʼ��ÿ��Ѱ�Ҿ���վ����-1����һվ������Ѱ��·��
		for (auto p = graphStation.FirstArc(vexLoc); p; p = graphStation.NextArc(vexLoc, p)) {
			if (graphStation.visit[p->adjvex] == graphStation.visit[vexLoc] - 1) {
				LeastStationRoute.path.emplace_back(graphStation.GetVex(p->adjvex));
				LeastStationRoute.bus.emplace_back(p->arcInf);
				++LeastStationRoute.station;
				vexLoc = p->adjvex;
				break;
			}
		}

	}
	++LeastStationRoute.station;

	//��ת·��
	std::reverse(LeastStationRoute.path.begin(), LeastStationRoute.path.end());
	std::reverse(LeastStationRoute.bus.begin(), LeastStationRoute.bus.end());

	for (int i = 1; i < LeastStationRoute.bus.size(); ++i) {
		if (LeastStationRoute.bus[i] != LeastStationRoute.bus[i - 1]) {
			LeastStationRoute.trans++;
		}
	}
	return LeastStationRoute;

}

route CreatRouteLeastTrans(GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus, vector<BusStationSearchInf> visit_leastTrans, int startLoc, int endLoc)
{
	route leastTransR;
	int cur_stationLoc = endLoc;



	while (cur_stationLoc != startLoc) {

		for (auto p = graphBus.FirstArc(graphBus.LocateVex(visit_leastTrans[cur_stationLoc].bus)); p; p = p->nextArc) {
			if (p->arcInf.name == graphStation.GetVex(cur_stationLoc)) {
				while (p->arcInf.name != graphStation.GetVex(visit_leastTrans[cur_stationLoc].preStationLoc)) {
					leastTransR.path.emplace_back(p->arcInf.name);
					leastTransR.bus.emplace_back(visit_leastTrans[cur_stationLoc].bus);
					leastTransR.station++;
					p = p->nextArc;
				}
				break;

			}
			else if (p->arcInf.name == graphStation.GetVex(visit_leastTrans[cur_stationLoc].preStationLoc)) {
				vector<string> st;
				while (p->arcInf.name != graphStation.GetVex(cur_stationLoc)) {
					st.emplace_back(p->arcInf.name);
					leastTransR.station++;
					leastTransR.bus.emplace_back(visit_leastTrans[cur_stationLoc].bus);
					p = p->nextArc;
				}
				if (cur_stationLoc == endLoc) {
					leastTransR.path.emplace_back(graphStation.GetVex(endLoc));
					leastTransR.station++;
				}

				std::reverse(st.begin(), st.end());
				leastTransR.path.insert(leastTransR.path.end(), st.begin(), st.end());
				break;
			}
		}


		cur_stationLoc = visit_leastTrans[cur_stationLoc].preStationLoc;


	}

	for (int i = 1; i < leastTransR.bus.size(); ++i) {
		if (leastTransR.bus[i] != leastTransR.bus[i - 1]) {
			leastTransR.trans++;
		}
	}

	std::reverse(leastTransR.path.begin(), leastTransR.path.end());
	std::reverse(leastTransR.bus.begin(), leastTransR.bus.end());
	return leastTransR;


}

/***************************************************************
  *  @brief     ����վ-վͼ�ҵ�һ����̵�·��
  *  @param     graphStation��վ-վͼ graphBus����-վͼ startStation�����վ endStation���յ�վ
  *  @note      ԭ������������������죩
 **************************************************************/
route FindRouteLeastTrans(GraphList<string, int>& graphStation, GraphList<int, stationInf>& graphBus, string startStation, string endStation) {

	LinkQueue<int> queue;
	int startLoc = graphStation.LocateVex(startStation);
	int endLoc = graphStation.LocateVex(endStation);
	vector<BusStationSearchInf> visit_leastTrans(graphStation.VexNum());//��������
	bool FIND = false;
	route leastTransR;

	queue.EnQueue(startLoc);//���վ���
	visit_leastTrans[startLoc].bus = graphStation.FirstArc(startLoc)->arcInf;//���վ
	visit_leastTrans[startLoc].visit = 0;

	while (queue.QueueEmpty() == false) {

		int cur_stationLoc = -1;
		queue.DeQueue(cur_stationLoc);

		if (cur_stationLoc == endLoc) {
			break;//�ҵ��յ�վֱ���˳�ѭ��
		}

		for (auto p = graphStation.FirstArc(cur_stationLoc); p; p = p->nextArc) {//�������վ�������·��

			for (auto q = graphBus.FirstArc(graphBus.LocateVex(p->arcInf)); q; q = q->nextArc) {//����·���ϳ��ε�����վ��

				int cur_bus = p->arcInf;

				if (q->arcInf.name == graphStation.GetVex(cur_stationLoc)) {//��λ����վ��
					auto temp_q = q;
					if (q->nextArc == nullptr) {//������յ�վ
						q = q->preArc;
						while (q) {//���ڳ���·���ϵ�ÿһ��վ�㣬��û�з��ʹ���������Ǵ�ʲôվ������ģ����趨���ʷ����궨����ʲô���ζ����ġ�
							if (visit_leastTrans[graphStation.LocateVex(q->arcInf.name)].visit == false) {

								int cur_stationLocline = graphStation.LocateVex(q->arcInf.name);
								queue.EnQueue(cur_stationLocline);
								visit_leastTrans[cur_stationLocline].visit = true;
								visit_leastTrans[cur_stationLocline].preStationLoc = cur_stationLoc;
								visit_leastTrans[cur_stationLocline].bus = cur_bus;
								if (cur_stationLocline == endLoc) {//����ҵ����յ�վ��ֱ�Ӵ�����·���ҷ���
									leastTransR = CreatRouteLeastTrans(graphStation, graphBus, visit_leastTrans, startLoc, endLoc);
									return leastTransR;
								}
							}

							q = q->preArc;
						}
					}
					else if (q->preArc == nullptr) {//��������վ

						q = q->nextArc;
						while (q) {//���ڳ���·���ϵ�ÿһ��վ�㣬��û�з��ʹ���������Ǵ�ʲôվ������ģ����趨���ʷ����궨����ʲô���ζ����ġ�

							if (visit_leastTrans[graphStation.LocateVex(q->arcInf.name)].visit == false) {
								int cur_stationLocline = graphStation.LocateVex(q->arcInf.name);
								queue.EnQueue(cur_stationLocline);
								visit_leastTrans[cur_stationLocline].visit = true;
								visit_leastTrans[cur_stationLocline].preStationLoc = cur_stationLoc;
								visit_leastTrans[cur_stationLocline].bus = cur_bus;
								if (cur_stationLocline == endLoc) {//����ҵ����յ�վ��ֱ�Ӵ�����·���ҷ���
									leastTransR = CreatRouteLeastTrans(graphStation, graphBus, visit_leastTrans, startLoc, endLoc);
									return leastTransR;
								}
							}
							q = q->nextArc;

						}

					}
					else {//���վ�����м�
						auto r = q->nextArc;
						auto s = q->preArc;
						while (r) {//���ڳ���·���ϵ�ÿһ��վ�㣬��û�з��ʹ���������Ǵ�ʲôվ������ģ����趨���ʷ����궨����ʲô���ζ����ġ�
							if (visit_leastTrans[graphStation.LocateVex(r->arcInf.name)].visit == false) {
								int cur_stationLocline = graphStation.LocateVex(r->arcInf.name);
								queue.EnQueue(cur_stationLocline);
								visit_leastTrans[cur_stationLocline].visit = true;
								visit_leastTrans[cur_stationLocline].preStationLoc = cur_stationLoc;
								visit_leastTrans[cur_stationLocline].bus = cur_bus;
								if (cur_stationLocline == endLoc) {//����ҵ����յ�վ��ֱ�Ӵ�����·���ҷ���
									leastTransR = CreatRouteLeastTrans(graphStation, graphBus, visit_leastTrans, startLoc, endLoc);
									return leastTransR;
								}
							}
							r = r->nextArc;

						}
						while (s) {//���ڳ���·���ϵ�ÿһ��վ�㣬��û�з��ʹ���������Ǵ�ʲôվ������ģ����趨���ʷ����궨����ʲô���ζ����ġ�
							if (visit_leastTrans[graphStation.LocateVex(s->arcInf.name)].visit == false) {
								int cur_stationLocline = graphStation.LocateVex(s->arcInf.name);
								queue.EnQueue(cur_stationLocline);
								visit_leastTrans[cur_stationLocline].visit = true;
								visit_leastTrans[cur_stationLocline].preStationLoc = cur_stationLoc;
								visit_leastTrans[cur_stationLocline].bus = cur_bus;
								if (cur_stationLocline == endLoc) {//����ҵ����յ�վ��ֱ�Ӵ�����·���ҷ���
									leastTransR = CreatRouteLeastTrans(graphStation, graphBus, visit_leastTrans, startLoc, endLoc);
									return leastTransR;
								}
							}
							s = s->preArc;

						}

					}

					break;
				}
			}
		}

	}//end of while (queue.QueueEmpty() == false) 

	//����ҵ����յ�վ��ֱ�Ӵ�����·���ҷ���
	leastTransR = CreatRouteLeastTrans(graphStation, graphBus, visit_leastTrans, startLoc, endLoc);
	return leastTransR;

}
