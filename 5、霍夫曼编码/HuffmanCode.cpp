#include"HuffmanCode.h"


int main(int argc, char* argv[]) {

	std::vector<int> weightList(ASCII_MAX, 0);

	std::ifstream fileIn("Huffman�������.txt",std::ios::in);
	std::ofstream fileDataOut("Huffman������.txt", std::ios::out | std::ios::trunc );
	std::ofstream fileCodeOut("Huffman����.huf", std::ios::out | std::ios::trunc | std::ios::binary);
	std::ofstream fileDeCodeOut("Huffman����.txt", std::ios::out | std::ios::trunc);

	
	std::vector<HuffmanList> huffmanList = CreateHuffmanTree(fileIn, weightList);
	std::vector<HuffmanCode> huffmanCodeList= CreateCodeInf(fileDataOut, huffmanList);
	
	fileDataOut.close();
	fileIn.close();
	fileIn.open("Huffman�������.txt", std::ios::in);

	WriteHuffmanCode(fileIn, fileCodeOut, huffmanList,huffmanCodeList);
	
	fileCodeOut.close();
	fileIn.close();
	fileIn.open("Huffman����.huf", std::ios::in | std::ios::binary);
	
	ReadHuffmanCode(fileIn, fileDeCodeOut, huffmanList,huffmanCodeList);

	return EXIT_SUCCESS;
}