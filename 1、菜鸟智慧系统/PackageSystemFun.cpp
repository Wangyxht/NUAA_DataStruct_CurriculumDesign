#include"PackageSystem.h"

char systemMenu()
{
	using std::cout;
	using std::cin;
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << "\n\t\t\t\t\t\t菜鸟驿站收发演示\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t1）演示下一天 \t\t2) 查询快递\t\tq）退出\n";
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

std::string QueryMenu()
{
	using std::cout;
	using std::cin;
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << "\n\t\t\t\t\t\t菜鸟驿站收发演示\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t\t\t请输入查询手机号或包裹编号：";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	
	std::string input;
	cin >> input;
	fflush(stdin);
	system("cls");
	if (input.empty() == false && input.length() <= 4 || input.length() == 11) {
		return input;
	}
	else {
		cout << '\n';
		cout << '\n';
		cout << '\n';
		cout << '\n';
		cout << '\n';
		cout << "\t\t\t-------------------------------------------------------------------";
		cout << '\n';
		cout << "\n\t\t\t\t\t\t菜鸟驿站收发演示\n";
		cout << "\t\t\t-------------------------------------------------------------------";
		cout << '\n';
		cout << '\n';
		cout << '\n';
		cout << "\n\t\t\t\t\t输入有误！";
		cout << '\n';
		cout << '\n';
		cout << '\n';
		cout << "\t\t\t-------------------------------------------------------------------";
		cout << '\n';
		system("pause");
		return "";
	}
}

std::vector<Person> ReadPerson(std::ifstream& fileIn)
{
	std::vector<Person> addressBook;

	while (fileIn.eof() == false) {
		std::string name;
		std::string tele;

		fileIn >> name >> tele;
		Person person(name, tele);
		addressBook.push_back(person);

	}

	return addressBook;
}
//快递随机入站
void RandomGeneratedPackages(Shelf& shelf, std::vector<Person> &addressBook,Date date, std::ofstream& fileOut)
{
	std::default_random_engine dre(static_cast<unsigned int> (time(0)));//随机数引擎
	std::uniform_int_distribution<int> packageAddressee_r(0, addressBook.size()-1);//收件人随机数
	std::vector<int> packageInNum(addressBook.size(), 0);
	for (int i = SMALL; i <= LARGE; ++i) {
		std::uniform_int_distribution<int> packageNum_r(0, shelf.Capability(i));
		int packageNum = packageNum_r(dre);
		for (int j = 0; j < packageNum; ++j) {
			int packageAddressee = packageAddressee_r(dre);
			Package newPackage(i, date, addressBook[packageAddressee]);
			addressBook[packageAddressee].PackageCome();
			packageInNum[packageAddressee]++;
			newPackage.CreateID(shelf.GetLeastID(i));
			shelf.PackageIn(newPackage);
			fileOut << "-----------------------------\n";
			fileOut << "[!]新包裹信息:\n" << newPackage;
			
		}
	}
	std::cout << std::accumulate(packageInNum.begin(), packageInNum.end(), 0) << "件快递已到达\n\n";
	fileOut << "-----------------------------\n";

	std::cout << "-----------------------------\n\n";
	std::cout << "平均每人到达" << static_cast<float> (std::accumulate(packageInNum.begin(), packageInNum.end(), 0)) / addressBook.size() << "件快递。\n\n";
	std::cout << "-----------------------------\n\n";

	fileOut << "-----------------------------\n\n";
	fileOut << "平均每人到达" << static_cast<float> (std::accumulate(packageInNum.begin(), packageInNum.end(), 0)) / addressBook.size() << "件快递。\n\n";
	fileOut << "-----------------------------\n\n";
	return;

}
//快递随机被取走
void RandomCollectPackages(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut) {
	std::default_random_engine dre(static_cast<unsigned int> (time(0)));//随机数引擎
	std::uniform_int_distribution<int> collect_r(0, 100);//取快递触发参数
	Person maxCollectPerson;
	int maxCollectNum = 0;

	for (int i = 0; i < addressBook.size(); ++i) {
		if (addressBook[i].HasPackage()) {
			int collect = collect_r(dre);
			if (collect >= 50) {
				std::vector<Package> collectPakage = shelf.PackageCollect(addressBook[i]);
				addressBook[i].PackageCollect();

				fileOut <<"[!]" << addressBook[i].Name() << "取走了以下编号的快递:\n";
				int collectNum = 0;
				for (auto package : collectPakage) {
					fileOut << package.GetID() << ' ';
					++collectNum;
					
				}
				if (maxCollectNum < collectNum) {
					maxCollectNum = collectNum;
					maxCollectPerson = addressBook[i];
				}
				fileOut << "\n";
				fileOut << "-----------------------------\n";
				
			}
			else{

				continue;
			}
		}

	}
	fileOut << "-----------------------------\n\n";
	fileOut << maxCollectPerson.Name() << "在" << date << "取走了最多的快件，个数为" << maxCollectNum << "件。\n\n";
	fileOut << "-----------------------------\n\n";

	std::cout << "快件取件过程完成\n\n";

	std::cout << "-----------------------------\n\n";
	std::cout << maxCollectPerson.Name() << "在" << date << "取走了最多的快件，个数为" << maxCollectNum << "件。\n\n";
	std::cout << "-----------------------------\n\n";

	return;
}

void RefreshPackage(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut)
{
	std::vector<Package> returnPackage=shelf.PackageRefresh();
	fileOut << "-----------------------------\n\n";
	for (auto package : returnPackage) {
		fileOut << package.GetID() << "号包裹逾期退回。\n";
	}
	fileOut << "-----------------------------\n\n";
	fileOut << returnPackage.size() << "件包裹逾期退回。\n";
	fileOut << "-----------------------------\n\n";

	std::cout << returnPackage.size() << "件包裹逾期退回。\n\n";
	std::cout << "-----------------------------\n\n";
	return;
}

