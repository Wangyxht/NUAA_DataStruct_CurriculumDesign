#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include"Bits8.h"

#define ASCII_MAX 128

static int charLen = 0;

struct HuffmanList
{
	short int ASCII;
	int weight;
	int lchild;
	int rchild;
	int parent;

};

struct HuffmanCode {
	short ch;
	std::string code;
};


//构建权值表
std::vector<HuffmanList> CreateHuffmanTree(std::ifstream &fileIn,std::vector<int> weightList);

//找到两个最小权值的树
std::pair<int, int> FindLeastWeightTree(std::vector<HuffmanList> huffmanList, int n);

//输出编码 字符基本信息
std::vector<HuffmanCode> CreateCodeInf(std::ofstream & fileOut, std::vector<HuffmanList> huffmanList);

//写入编码
void WriteHuffmanCode(std::ifstream& fileIn, std::ofstream& fileOut, std::vector<HuffmanList> huffmanList, std::vector<HuffmanCode> huffmanCodeList);

//解码
void ReadHuffmanCode(std::ifstream& fileIn, std::ofstream& fileOut, std::vector<HuffmanList> huffmanList, std::vector<HuffmanCode> huffmanCodeList);

#endif // !_HUFFMAN_TREE_H_
