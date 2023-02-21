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
	cout << "\n\t\t\t\t\t\t������վ�շ���ʾ\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t1����ʾ��һ�� \t\t2) ��ѯ���\t\tq���˳�\n";
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
	cout << "\n\t\t\t\t\t\t������վ�շ���ʾ\n";
	cout << "\t\t\t-------------------------------------------------------------------";
	cout << '\n';
	cout << '\n';
	cout << '\n';
	cout << "\n\t\t\t\t\t�������ѯ�ֻ��Ż������ţ�";
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
		cout << "\n\t\t\t\t\t\t������վ�շ���ʾ\n";
		cout << "\t\t\t-------------------------------------------------------------------";
		cout << '\n';
		cout << '\n';
		cout << '\n';
		cout << "\n\t\t\t\t\t��������";
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
//��������վ
void RandomGeneratedPackages(Shelf& shelf, std::vector<Person> &addressBook,Date date, std::ofstream& fileOut)
{
	std::default_random_engine dre(static_cast<unsigned int> (time(0)));//���������
	std::uniform_int_distribution<int> packageAddressee_r(0, addressBook.size()-1);//�ռ��������
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
			fileOut << "[!]�°�����Ϣ:\n" << newPackage;
			
		}
	}
	std::cout << std::accumulate(packageInNum.begin(), packageInNum.end(), 0) << "������ѵ���\n\n";
	fileOut << "-----------------------------\n";

	std::cout << "-----------------------------\n\n";
	std::cout << "ƽ��ÿ�˵���" << static_cast<float> (std::accumulate(packageInNum.begin(), packageInNum.end(), 0)) / addressBook.size() << "����ݡ�\n\n";
	std::cout << "-----------------------------\n\n";

	fileOut << "-----------------------------\n\n";
	fileOut << "ƽ��ÿ�˵���" << static_cast<float> (std::accumulate(packageInNum.begin(), packageInNum.end(), 0)) / addressBook.size() << "����ݡ�\n\n";
	fileOut << "-----------------------------\n\n";
	return;

}
//��������ȡ��
void RandomCollectPackages(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut) {
	std::default_random_engine dre(static_cast<unsigned int> (time(0)));//���������
	std::uniform_int_distribution<int> collect_r(0, 100);//ȡ��ݴ�������
	Person maxCollectPerson;
	int maxCollectNum = 0;

	for (int i = 0; i < addressBook.size(); ++i) {
		if (addressBook[i].HasPackage()) {
			int collect = collect_r(dre);
			if (collect >= 50) {
				std::vector<Package> collectPakage = shelf.PackageCollect(addressBook[i]);
				addressBook[i].PackageCollect();

				fileOut <<"[!]" << addressBook[i].Name() << "ȡ�������±�ŵĿ��:\n";
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
	fileOut << maxCollectPerson.Name() << "��" << date << "ȡ�������Ŀ��������Ϊ" << maxCollectNum << "����\n\n";
	fileOut << "-----------------------------\n\n";

	std::cout << "���ȡ���������\n\n";

	std::cout << "-----------------------------\n\n";
	std::cout << maxCollectPerson.Name() << "��" << date << "ȡ�������Ŀ��������Ϊ" << maxCollectNum << "����\n\n";
	std::cout << "-----------------------------\n\n";

	return;
}

void RefreshPackage(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut)
{
	std::vector<Package> returnPackage=shelf.PackageRefresh();
	fileOut << "-----------------------------\n\n";
	for (auto package : returnPackage) {
		fileOut << package.GetID() << "�Ű��������˻ء�\n";
	}
	fileOut << "-----------------------------\n\n";
	fileOut << returnPackage.size() << "�����������˻ء�\n";
	fileOut << "-----------------------------\n\n";

	std::cout << returnPackage.size() << "�����������˻ء�\n\n";
	std::cout << "-----------------------------\n\n";
	return;
}

