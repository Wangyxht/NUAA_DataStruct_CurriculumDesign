#include"Sort.h"

int main(int argc, char* argv[]) {
	
	int test[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//²âÊÔÓÃÀıÉú³É
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

	//²âÊÔÓÃÀı¼ÓÔØ
	std::vector<std::vector<int>> sampleList(10);//²âÊÔ¼¯
	for (int i = 0; i < 10; ++i) {
		std::string sampleFileName = "Sample" + std::to_string(i+1) + ".txt";
		std::ifstream Sample(sampleFileName, std::ios::in);
		sampleList[i] = LoadSample(Sample);
	}

	void (*sortFun_)(int*, int);
	void (*shellSort_)(int*, int, std::vector<int>);

	std::cout << "\t\t\t\tÅÅĞòËã·¨²âÊÔ\n--------------------------------------------------------------------------------------------------\n";
	std::cout << "ÅÅĞòËã·¨\tÉıĞò\tµ¹Ğò\tÑùÀı3\tÑùÀı4\tÑùÀı5\tÑùÀı6\tÑùÀı7\tÑùÀı8\tÑùÀı9\tÑùÀı10\n";
	
	//Ñ¡ÔñÅÅĞò²âÊÔ
	std::cout << "\nSelect:\t\t";
	sortFun_ = SelectSort;
	TestSortFun(sampleList, sortFun_);

	//¼òµ¥²åÈëÅÅĞò²âÊÔ
	std::cout << "\nInsert:\t\t";
	sortFun_ = InsertSort;
	TestSortFun(sampleList, sortFun_);
	
	//Ï£¶ûÅÅĞò²âÊÔ
	std::cout << "\nShell:\t\t";
	shellSort_ = ShellSort;
	TestSortFun(sampleList, shellSort_);

	//Ã°ÅİÅÅĞò²âÊÔ
	std::cout << "\nBubble:\t\t";
	sortFun_ = BubbleSort;
	TestSortFun(sampleList, sortFun_);

	//¿ìËÙÅÅĞò²âÊÔ
	std::cout << "\nQuick:\t\t";
	sortFun_ = QuickSort;
	TestSortFun(sampleList, sortFun_);

	//¶ÑÅÅĞò²âÊÔ
	std::cout << "\nHeap:\t\t";
	sortFun_ = HeapSort;
	TestSortFun(sampleList, sortFun_);

	//¹é²¢ÅÅĞò²âÊÔ
	std::cout << "\nMerge:\t\t";
	sortFun_ = MergeSort;
	TestSortFun(sampleList, sortFun_);
	
	//»ùÊıÅÅĞò²âÊÔ
	std::cout << "\nRedix:\t\t";
	sortFun_ = RedixSort;
	TestSortFun(sampleList, sortFun_);


	std::cout << "\n--------------------------------------------------------------------------------------------------\n";
	return EXIT_SUCCESS;
}