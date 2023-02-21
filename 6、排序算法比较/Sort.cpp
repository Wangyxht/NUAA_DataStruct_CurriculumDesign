#include"Sort.h"

int main(int argc, char* argv[]) {
	
	int test[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//������������
	for (int i = 1; i <= 10; ++i) {
		std::string sampleFileName = "Sample" + std::to_string(i) + ".txt";
		std::ofstream Sample(sampleFileName, std::ios::out | std::ios::trunc);
		if (Sample.fail()) {
			throw "file cannot open";
			exit(EXIT_FAILURE);
		}
		
		if (i == 1) {
			CreateTestSamples(Sample, ASCEND_SAMPLE);
		}
		else if (i == 2) {
			CreateTestSamples(Sample, DESEND_SAMPLE);
		}
		else {
			CreateTestSamples(Sample);
			Sleep(1000);
		}

		Sample.close();
	}

	//������������
	std::vector<std::vector<int>> sampleList(10);//���Լ�
	for (int i = 0; i < 10; ++i) {
		std::string sampleFileName = "Sample" + std::to_string(i+1) + ".txt";
		std::ifstream Sample(sampleFileName, std::ios::in);
		sampleList[i] = LoadSample(Sample);
	}

	void (*sortFun_)(int*, int);
	void (*shellSort_)(int*, int, std::vector<int>);

	std::cout << "\t\t\t\t�����㷨����\n--------------------------------------------------------------------------------------------------\n";
	std::cout << "�����㷨\t����\t����\t����3\t����4\t����5\t����6\t����7\t����8\t����9\t����10\n";
	
	//ѡ���������
	std::cout << "\nSelect:\t\t";
	sortFun_ = SelectSort;
	TestSortFun(sampleList, sortFun_);

	//�򵥲����������
	std::cout << "\nInsert:\t\t";
	sortFun_ = InsertSort;
	TestSortFun(sampleList, sortFun_);
	
	//ϣ���������
	std::cout << "\nShell:\t\t";
	shellSort_ = ShellSort;
	TestSortFun(sampleList, shellSort_);

	//ð���������
	std::cout << "\nBubble:\t\t";
	sortFun_ = BubbleSort;
	TestSortFun(sampleList, sortFun_);

	//�����������
	std::cout << "\nQuick:\t\t";
	sortFun_ = QuickSort;
	TestSortFun(sampleList, sortFun_);

	//���������
	std::cout << "\nHeap:\t\t";
	sortFun_ = HeapSort;
	TestSortFun(sampleList, sortFun_);

	//�鲢�������
	std::cout << "\nMerge:\t\t";
	sortFun_ = MergeSort;
	TestSortFun(sampleList, sortFun_);
	
	//�����������
	std::cout << "\nRedix:\t\t";
	sortFun_ = RedixSort;
	TestSortFun(sampleList, sortFun_);


	std::cout << "\n--------------------------------------------------------------------------------------------------\n";
	return EXIT_SUCCESS;
}