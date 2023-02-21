#ifndef SORT_H_
#define SORT_H_

#define RANDOM_SAMPLE 1
#define ASCEND_SAMPLE 2
#define DESEND_SAMPLE 3
#define SAMPLE_MAX_NUM 50000
const static long long INT_MAX_DIGIT = 1000000000;

#include<ctime>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<Windows.h>
#include"LinkQueue.hpp"

//���ɲ�������
void CreateTestSamples(std::ofstream& fileOut, int mode=RANDOM_SAMPLE);

//��ȡ��������
std::vector<int> LoadSample(std::ifstream& fileIn);

//���Ժ���
void TestSortFun(std::vector<std::vector<int>> sampleList, void(*SortFun)(int list[],int n));
void TestSortFun(std::vector<std::vector<int>> sampleList, void(*SortFun)(int list[], int n, std::vector<int> increase));

//�򵥲�������
void InsertSort(int list[], int n);

//ϣ������
static const std::vector<int> shellIncrease = { 7,5,3,1 };
void ShellSort(int list[], int n, std::vector<int> increase = shellIncrease);
void ShellSort(int list[], int increase, int n);

//�򵥽�������
void BubbleSort(int list[], int n);

//��������
void QuickSort(int list[], int n);
void QuickSort(int list[], int start, int end);
int Partation(int list[], int start, int end);

//��������
template<class T> 
void Swap(T& numA, T& numB);

//ѡ������
void SelectSort(int list[], int n);

//������
void HeapSort(int list[], int n);

void MaxHeapify(int list[], int i, int heapSize);
inline int LeftChild(int loc);
inline int RightChild(int loc);

//�鲢����
void MergeSort(int list[], int n);
void MergeSort(int list[], int n, int len);

void Merge(int list[], int strat,int mid, int high);

//��������
void RedixSort(int list[], int n);

#endif