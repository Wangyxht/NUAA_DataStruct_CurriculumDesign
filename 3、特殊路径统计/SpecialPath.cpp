#include"SpecialPath.h"

int main(int argc, char* argv[]) {

	GraphMat<int> graph;
	graph.CreatGraph();
	//graph.ShowMat();
	vector<vector<vector<int>>> pathList = SearchAllPath(graph);
	std::cout << CheckSpecialPath(pathList) << "\n";

	return EXIT_SUCCESS;
}


