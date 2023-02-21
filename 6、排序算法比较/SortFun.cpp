#include"Sort.h"

//在文件中创建一个测试用例
void CreateTestSamples(std::ofstream& fileOut, int mode)
{
	if (mode == RANDOM_SAMPLE) {
		std::default_random_engine dre((unsigned int)time(0));
		std::uniform_int_distribution<int> di(0, INT_MAX);
		for (int i = 1; i <= SAMPLE_MAX_NUM; ++i) {
			fileOut << di(dre) << " ";
		}
	}
	else if (mode == DESEND_SAMPLE) {
		for (int i = SAMPLE_MAX_NUM; i >= 1; --i) {
			fileOut << i << " ";
		}
	}
	else if (mode == ASCEND_SAMPLE) {
		for (int i = 1; i <= SAMPLE_MAX_NUM; ++i) {
			fileOut << i << " ";
		}
	}

	return;
}

//加载一个测试用例
std::vector<int> LoadSample(std::ifstream& fileIn)
{
	std::vector<int> sample;
	for (int i = 0; i <= SAMPLE_MAX_NUM; ++i) {
		int sampleNum;
		fileIn >> sampleNum;
		sample.emplace_back(sampleNum);
	}

	return sample;
}

void TestSortFun(std::vector<std::vector<int>> sampleList, void(*SortFun)(int list[], int n))
{
	clock_t timeBegin;
	clock_t timeEnd;
	for (int i = 0; i < 10; ++i) {
		int* sample = new int[SAMPLE_MAX_NUM];
		memcpy(sample, &sampleList[i][0], (sampleList[i].size() - 1) * sizeof(int));
		timeBegin = clock();
		SortFun(sample, SAMPLE_MAX_NUM);
		timeEnd = clock();
		delete[] sample;
		std::cout << timeEnd - timeBegin << "ms\t";
	}
}

void TestSortFun(std::vector<std::vector<int>> sampleList, void(*SortFun)(int list[], int n, std::vector<int>increase))
{
	clock_t timeBegin;
	clock_t timeEnd;
	for (int i = 0; i < 10; ++i) {
		int* sample = new int[SAMPLE_MAX_NUM];
		memcpy(sample, &sampleList[i][0], (sampleList[i].size() - 1) * sizeof(int));
		timeBegin = clock();
		SortFun(sample, SAMPLE_MAX_NUM, shellIncrease);
		timeEnd = clock();
		delete[] sample;
		std::cout << timeEnd - timeBegin << "ms\t";
	}
}

void InsertSort(int list[], int n)
{
	for (int i = 0; i < n; ++i) {
		int temp = list[i];
		int j = i - 1;
		while (j >= 0 && list[j] > temp) {
			list[j + 1] = list[j];
			--j;
		}
		list[j + 1] = temp;
	}

	return;
}

void ShellSort(int list[], int n, std::vector<int> increase)
{
	for (int i = 0; i < increase.size(); ++i) {
		ShellSort(list, increase[i], n);
	}
}

void ShellSort(int list[], int increase, int n)
{
	for (int i = 0; i < n; ++i) {
		int temp = list[i];
		int j = i - increase;
		while (j >= 0 && list[j] > temp) {
			list[j + increase] = list[j];
			j -= increase;
		}
		list[j + increase] = temp;
	}

	return;
}

void BubbleSort(int list[], int n)
{

	for (int i = 0; i < n; ++i) {
		bool has_swap = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (list[j] > list[j + 1]) {
				Swap(list[j + 1], list[j]);
				has_swap = true;
			}
		}
		if (has_swap == false) {
			return;
		}
	}
	return;
}

void QuickSort(int list[], int n)
{
	QuickSort(list, 0, n - 1);
}

void QuickSort(int list[], int start, int end)
{
	if (start < end) {
		int pivotLoc = Partation(list, start, end);
		QuickSort(list, start, pivotLoc - 1);
		QuickSort(list, pivotLoc + 1, end);
	}
	return;
}

int Partation(int list[], int start, int end)
{
	std::default_random_engine dre((unsigned int)time(0));
	std::uniform_int_distribution<int> di(start, end);
	int i = start;
	int j = end;
	Swap(list[start], list[di(dre)]);
	int pivotNum = list[start];

	while (j > i) {
		while (j > i && list[j] >= pivotNum) --j;
		list[i] = list[j];

		while (j > i && list[i] <= pivotNum) ++i;
		list[j] = list[i];
	}
	list[i] = pivotNum;
	return i;
}

void SelectSort(int list[], int n)
{
	for (int i = 0; i < n - 1; ++i) {
		int minLoc = i + 1;
		for (int j = i + 1; j < n; ++j) {
			if (list[minLoc] > list[j]) {
				minLoc = j;
			}
		}
		Swap(list[i], list[minLoc]);
	}
	return;
}

void HeapSort(int list[], int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--) {
		MaxHeapify(list, i, n);
	}

	for (int i = n - 1; i >= 0; i--) {
		Swap(list[0], list[i]);
		MaxHeapify(list, 0, i - 1);
	}

	return;
}

void MaxHeapify(int list[], int i, int heapSize)
{
	int lchild = LeftChild(i);
	int rchild = RightChild(i);

	while (lchild <= heapSize) {
		if (rchild <= heapSize) {

			if (list[i] > list[rchild] && list[i] > list[lchild]) break;
			else if (list[rchild] >= list[lchild]) {//左孩子大
				Swap(list[i], list[rchild]);
				i = rchild;
				lchild = LeftChild(i);
				rchild = RightChild(i);
			}
			else if (list[rchild] <= list[lchild]) {//右孩子大
				Swap(list[i], list[lchild]);
				i = lchild;
				lchild = LeftChild(i);
				rchild = RightChild(i);
			}
		}
		else {
			if (list[i] > list[lchild]) break;

			else if (list[i] < list[lchild]) {
				Swap(list[i], list[lchild]);
				i = lchild;
				lchild = LeftChild(i);
				rchild = RightChild(i);
			}
		}
	}

	return;
}

inline int LeftChild(int loc)
{
	return 2 * loc + 1;
}

inline int RightChild(int loc)
{
	return 2 * loc + 2;
}

void MergeSort(int list[], int n)
{
	for (int len = 1; len < n; len *= 2) {
		MergeSort(list, n - 1, len);
	}
}

void MergeSort(int list[], int n, int len)
{
	int i = 0;
	while (i + 2 * len <= n) {
		Merge(list, i, i + len - 1, i + 2 * len - 1);
		i = i + 2 * len;
	}

	if (i + len <= n) {
		Merge(list, i, i + len - 1, n);
	}
}

void Merge(int list[], int start, int mid, int end)
{
	int* tempList = new int[end - start + 1];
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end) {
		if (list[i] <= list[j]) {
			tempList[k] = list[i];
			++k;
			++i;
		}
		else {
			tempList[k] = list[j];
			++k;
			++j;
		}
	}


	while (j <= end) {
		tempList[k] = list[j];
		++k;
		++j;
	}

	while (i <= mid) {
		tempList[k] = list[i];
		++k;
		++i;
	}

	for (i = start, k = 0; i <= end; ++i, ++k) {
		list[i] = tempList[k];
	}

	delete[] tempList;
	return;
}

void RedixSort(int list[], int n)
{
	LinkQueue<int> queue[10];
	long long radix;
	long long maxRadix = INT_MAX_DIGIT * 10;

	for (radix = 10; radix <= maxRadix; radix *= 10) {
		//队列分配
		for (int i = 0; i < n; ++i) {
			int digit = (list[i] % radix) / (radix / 10);
			queue[digit].EnQueue(list[i]);
		}

		//队列回收
		int j = 0;
		for (int i = 0; i < 10; ++i) {	
			while (queue[i].QueueEmpty() == false) {
				queue[i].DeQueue(list[j]);
				++j;
			}
		}
	}

	return;
}

template<class T>
void Swap(T& numA, T& numB) {
	T temp = numB;
	numB = numA;
	numA = temp;
}