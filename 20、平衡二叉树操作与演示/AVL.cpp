#include"AVL.hpp"
#include<iostream>
#include<random>
#include<fstream>
#include<ctime>

char Menu();

int main(int argc, char** argv) {

	AVL<int> AVLtree;
	//��testNum.txt���������30����
	static const int nums = 30;
	std::ofstream fileOut("testNum.txt", std::ios::out | std::ios::trunc);
	std::default_random_engine dre(static_cast<unsigned int> (time(0)));
	std::uniform_int_distribution<int> di(0, 99999);
	for (int i = 0; i < nums; ++i) {
		fileOut << di(dre) << " ";
	}
	fileOut.close();

	//��testNum.txt�ж�ȡ30����������ASL
	std::ifstream fileIn("testNum.txt", std::ios::in);
	for (int i = 0; i < nums; ++i) {
		int num_cur;
		fileIn >> num_cur;
		AVLtree.Insert(num_cur);
	}

	while (true) {
		system("cls");
		char choice = Menu();
		system("cls");
		switch (choice) {
			int input;
		case'1':
			std::cout << "\n\n��!�����������������ݣ�\n";
			std::cin >> input;
			if (AVLtree.Insert(input) == 0)
				std::cout << "��X������ʧ�ܣ��������ݴ��ڣ�\n";
			else
				std::cout << "���̡�����ɹ���������ͼ�λ���ʾ��֤��\n";
			system("pause");
			break;
		case'2':
			std::cout << "\n\n��!���������ɾ�������ݣ�\n";
			std::cin >> input;
			if (AVLtree.Delete(input) == 0)
				std::cout << "��X��ɾ��ʧ�ܣ��������ݲ����ڣ�\n";
			else
				std::cout << "���̡�ɾ���ɹ���������ͼ�λ���ʾ��֤��\n";
			system("pause");
			break;
		case'3':
			std::cout << "\n\n��!������������ҵ����ݣ�\n";
			std::cin >> input;
			if (AVLtree.Find(input))
				std::cout << "���̡�" << input << "������ƽ���������\n";
			else
				std::cout << "��X������ʧ�ܣ��������ݲ����ڣ�\n";
			system("pause");
			break;
		case'4':
			AVLtree.DisplayAVL();
			system("pause");
			break;
		case'5':
			std::cout << "\n\n���̡�������������������У�\n";
			AVLtree.InOrderTraverse();
			std::cout << "\n\n���̡��������Ĳ�α������У�\n";
			AVLtree.LevelOrderTraverse();
			system("pause");
			break;
		case'q':
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}

	return EXIT_SUCCESS;
}

char Menu() {
	using std::cin;
	using std::cout;
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << "\n\t\t\t\t\t\tAVL������ʾ\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t\t1������\t\t\t\t2)ɾ��\n";
	cout << "\n\t\t\t\t3������\t\t\t\t4)ͼ�λ����\n";
	cout << "\n\t\t\t\t5) ��ȡ��������\t\t\tq)�˳�\n";
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