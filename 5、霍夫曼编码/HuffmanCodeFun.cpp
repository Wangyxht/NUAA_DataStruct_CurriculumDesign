#include"HuffmanCode.h"

std::vector<HuffmanList> CreateHuffmanTree(std::ifstream &fileIn, std::vector<int> weightList)
{
	char ch;

	while (fileIn.eof()==false) {
		fileIn.get(ch);
		weightList[ch]++;
		charLen++;
		
	}

	int chNum = 0;
	for (int i = 0; i < ASCII_MAX; ++i) {
		if (weightList[i] != 0) {
			chNum++;
		}
	}

	std::vector<HuffmanList>  hufflmanCodeList(chNum * 2 - 1);

	for (int i = 0 , j = 0; i < ASCII_MAX; ++i) {
		if (weightList[i] != 0) {
			hufflmanCodeList[j].weight = weightList[i];
			hufflmanCodeList[j].ASCII = i;
			hufflmanCodeList[j].parent = j;
			hufflmanCodeList[j].lchild = -1;
			hufflmanCodeList[j].rchild = -1;
			++j;
		}
	}

	for (int i = chNum; i < 2 * chNum -1; ++i) {
		std::pair<int, int> twoLeastTree = FindLeastWeightTree(hufflmanCodeList, i);
		hufflmanCodeList[i].ASCII = -1;
		hufflmanCodeList[i].lchild = twoLeastTree.first;
		hufflmanCodeList[i].rchild = twoLeastTree.second;
		hufflmanCodeList[i].weight = hufflmanCodeList[twoLeastTree.first].weight + hufflmanCodeList[twoLeastTree.second].weight;
		hufflmanCodeList[i].parent = i;

		hufflmanCodeList[twoLeastTree.first].parent = i;
		hufflmanCodeList[twoLeastTree.second].parent = i;
	}
	

	return hufflmanCodeList;
}

std::pair<int, int> FindLeastWeightTree(std::vector<HuffmanList> huffmanList, int n)
{
	std::pair<int, int> twoLeastTree;
	//找最小
	int minWeight = INT_MAX;
	for (int i = 0; i < n; ++i) {
		if (huffmanList[i].parent==i && huffmanList[i].weight < minWeight) {
			twoLeastTree.first = i;
			minWeight = huffmanList[i].weight;
		}
	}

	//找次小
	minWeight = INT_MAX;
	for (int i = 0; i < n; ++i) {
		if (huffmanList[i].parent == i && i!=twoLeastTree.first && huffmanList[i].weight < minWeight) {
			twoLeastTree.second = i;
			minWeight = huffmanList[i].weight;
		}
	}

	return twoLeastTree;
}

std::vector<HuffmanCode> CreateCodeInf(std::ofstream &fileOut, std::vector<HuffmanList> huffmanList)
{
	std::vector<HuffmanCode> huffmanCodeList;
	
	fileOut << "字符以及次数权值：\n";
	for (int i = 0; huffmanList[i].ASCII != -1; ++i) {

		if (huffmanList[i].ASCII == '\n') {
			fileOut << "\\n:" << huffmanList[i].weight << '\n';
		}
		else if (huffmanList[i].ASCII == '\0') {
			fileOut << "\\0:" << huffmanList[i].weight << '\n';
		}
		else if (huffmanList[i].ASCII == ' ') {
			fileOut << "SPACE:" << huffmanList[i].weight << '\n';
		}
		else {
			fileOut << static_cast<char> (huffmanList[i].ASCII) << ':' << huffmanList[i].weight << '\n';
		}

	}


	fileOut << "字符集编码：\n";
	for (int i = 0; huffmanList[i].ASCII != -1; ++i) {
		int j = i;
		std::string code;
		while (huffmanList[j].parent != j) {
			int temp = j;
			j = huffmanList[j].parent;
			if (huffmanList[j].lchild == temp) {
				code += '0';
			}
			else if (huffmanList[j].rchild == temp) {
				code += '1';
			}
		}
		std::reverse(code.begin(), code.end());
		huffmanCodeList.push_back(HuffmanCode{ huffmanList[i].ASCII, code });

		if (huffmanList[i].ASCII == '\n') {
			fileOut << "\\n:" << code << '\n';
		}
		else if (huffmanList[i].ASCII == '\0') {
			fileOut << "\\0:" << code << '\n';
		}
		else if (huffmanList[i].ASCII == ' ') {
			fileOut << "SPACE:" << code << '\n';
		}
		else {
			fileOut << static_cast<char> (huffmanList[i].ASCII) << ':' << code << '\n';
		}
		
	}

	return huffmanCodeList;
}

void WriteHuffmanCode(std::ifstream& fileIn, std::ofstream& fileOut, std::vector<HuffmanList> huffmanList, std::vector<HuffmanCode> huffmanCodeList)
{
	int writeCounter = 0;
	bits_8 bits8;
	char ch;

	fileOut.write(reinterpret_cast<char*>(&charLen), sizeof(charLen));

	while (fileIn.eof() == false) {
			
		fileIn.get(ch);
		for (int i = 0; i < huffmanCodeList.size(); ++i) {
			if (huffmanList[i].ASCII == ch) {
				int j = 0;
				while (huffmanCodeList[i].code[j]!='\0') {
					if (writeCounter == 8) {
						bits8.Write(fileOut);
						writeCounter = 0;
					}
					if (huffmanCodeList[i].code[j] == '0') {
						bits8.SetBit(0 ,7 - writeCounter);
						writeCounter++;
						j++;
					}
					else if (huffmanCodeList[i].code[j] == '1') {
						bits8.SetBit(1, 7 - writeCounter);
						writeCounter++;
						j++;
					}
				}
			}
		}
	}

	if (writeCounter != 0) {
		bits8.Write(fileOut);
	}


	return;
}

void ReadHuffmanCode(std::ifstream& fileIn, std::ofstream& fileOut, std::vector<HuffmanList> huffmanList, std::vector<HuffmanCode> huffmanCodeList)
{
	int fileCharNum;
	fileIn.read(reinterpret_cast<char*>(&fileCharNum), sizeof(fileCharNum));

	int len = 1;
	int j = huffmanList.size() - 1;
	while(len < fileCharNum && fileIn.eof() == false) {
		bits_8 bits8;
		int count = 0;
		bits8.Read(fileIn);

		for (int i = 0; len <= fileCharNum && i < 8; ++i) {
			unsigned short bit = bits8.GetHighBit();
			bits8 = bits8 << 1;

			switch (bit) {
			case 1:
				j = huffmanList[j].rchild;
				break;
			case 0:
				j = huffmanList[j].lchild;
				break;
			}

			if (huffmanList[j].ASCII != -1) {
				fileOut << static_cast<char> (huffmanList[j].ASCII);
				len++;
				j = huffmanList.size() - 1;
			}
		}
	
	}

}