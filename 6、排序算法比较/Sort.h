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

//Éú³É²âÊÔÑùÀı
void CreateTestSamples(std::ofstream& fileOut, int mode=RANDOM_SAMPLE);

//¶ÁÈ¡²âÊÔÑùÀı
std::vector<int> LoadSample(std::ifstream& fileIn);

//²âÊÔº¯Êı
void TestSortFun(std::vector<std::vector<int>> sampleList, void(*SortFun)(int list[],int n));
void TestSortFun(std::vector<std::vector<int>> sampleList, void(*SortFun)(int list[], int n, std::vector<int> increase));

//¼òµ¥²åÈëÅÅĞò
void InsertSort(int list[], int n);

//Ï£¶ûÅÅĞò
static const std::vector<int> shellIncrease = { 7,5,3,1 };
void ShellSort(int list[], int n, std::vector<int> increase = shellIncrease);
void ShellSort(int list[], int increase, int n);

//¼òµ¥½»»»ÅÅĞò
void BubbleSort(int list[], int n);

//¿ìËÙÅÅĞò
void QuickSort(int list[], int n);
void QuickSort(int list[], int start, int end);
int Partation(int list[], int start, int end);

//½»»»º¯Êı
template<class T> 
void Swap(T& numA, T& numB);

//Ñ¡ÔñÅÅĞò
void SelectSort(int list[], int n);

//¶ÑÅÅĞò
void HeapSort(int list[], int n);

void MaxHeapify(int list[], int i, int heapSize);
inline int LeftChild(int loc);
inline int RightChild(int loc);

//¹é²¢ÅÅĞò
void MergeSort(int list[], int n);
void MergeSort(int list[], int n, int len);

void Merge(int list[], int strat,int mid, int high);

//»ùÊıÅÅĞò
void RedixSort(int list[], int n);

#endif