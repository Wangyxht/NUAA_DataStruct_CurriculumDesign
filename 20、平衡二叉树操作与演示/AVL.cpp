#include"AVL.hpp"
#include<iostream>
#include<random>
#include<fstream>
#include<ctime>

char Menu();

int main(int argc, char** argv) {

	AVL<int> AVLtree;
	//在testNum.txt中随机产生30个数
	static const int nums = 30;
	std::ofstream fileOut("testNum.txt", std::ios::out | std::ios::trunc);
	std::default_random_engine dre(static_cast<unsigned int> (time(0)));
	std::uniform_int_distribution<int> di(0, 99999);
	for (int i = 0; i < nums; ++i) {
		fileOut << di(dre) << " ";
	}
	fileOut.close();

	//在testNum.txt中读取30个数并插入ASL
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
			std::cout << "\n\n【!】请输入待插入的数据：\n";
			std::cin >> input;
			if (AVLtree.Insert(input) == 0)
				std::cout << "【X】插入失败！输入数据存在！\n";
			else
				std::cout << "【√】插入成功！可以在图形化显示验证！\n";
			system("pause");
			break;
		case'2':
			std::cout << "\n\n【!】请输入待删除的数据：\n";
			std::cin >> input;
			if (AVLtree.Delete(input) == 0)
				std::cout << "【X】删除失败！输入数据不存在！\n";
			else
				std::cout << "【√】删除成功！可以在图形化显示验证！\n";
			system("pause");
			break;
		case'3':
			std::cout << "\n\n【!】请输入待查找的数据：\n";
			std::cin >> input;
			if (AVLtree.Find(input))
				std::cout << "【√】" << input << "存在于平衡二叉树中\n";
			else
				std::cout << "【X】查找失败！输入数据不存在！\n";
			system("pause");
			break;
		case'4':
			AVLtree.DisplayAVL();
			system("pause");
			break;
		case'5':
			std::cout << "\n\n【√】二叉树的中序遍历序列：\n";
			AVLtree.InOrderTraverse();
			std::cout << "\n\n【√】二叉树的层次遍历序列：\n";
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
	cout << "\n\t\t\t\t\t\tAVL操作演示\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t\t1）插入\t\t\t\t2)删除\n";
	cout << "\n\t\t\t\t3）查找\t\t\t\t4)图形化输出\n";
	cout << "\n\t\t\t\t5) 获取遍历序列\t\t\tq)退出\n";
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