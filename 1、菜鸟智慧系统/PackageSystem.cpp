#include"PackageSystem.h"

int main(int argc, char* argv[]) {

	std::ifstream personInput("Person.txt", std::ios::in);
	std::ofstream fileOut("data.txt", std::ios::out | std::ios::trunc);

	if (personInput.fail() || fileOut.fail()) {
		throw "File cannot open";
		exit(EXIT_FAILURE);

	}

	std::vector<Person> addressBook = ReadPerson(personInput);
	Shelf packageShelf;
	Date date(2022, 1, 1);
	int day = 0;


	do {
		char choice = systemMenu();

		switch (choice) {
		case '1': {
			system("cls");
			std::cout << date << "事件：\n";
			std::cout << "----------------------------------------------\n\n";
			fileOut << date << "事件：\n";
			fileOut << "----------------------------------------------\n\n";

			//随机产生快递
			RandomGeneratedPackages(packageShelf, addressBook, date, fileOut);
			//随机取走
			RandomCollectPackages(packageShelf, addressBook, date, fileOut);
			//清除滞留件
			RefreshPackage(packageShelf, addressBook, date, fileOut);

			++day;

			if (day % 7 == 0) {
				std::cout << "-----------------------------\n\n";
				std::cout << "本周退回件数：" << packageShelf.ShowPackageReturn_Weekly() << "\n\n";
				std::cout << "-----------------------------\n\n";
				fileOut << "-----------------------------\n\n";
				fileOut << "本周退回件数：" << packageShelf.ShowPackageReturn_Weekly() << "\n\n";
				fileOut << "-----------------------------\n\n";
				packageShelf.WeeklyRefresh();
			}

			system("pause");
			break;
		}
		case'2': {
			system("cls");
			std::string query = QueryMenu();

			if (query.empty()) {
				break;
			}
			else if (query.length() == 11) {
				system("cls");
				std::vector<Package> packageFind = packageShelf.PackageSearchPhone(query);
				if (packageFind.empty() == false) {
					for (auto package : packageFind) {
						std::cout << "-----------------------------\n\n";
						std::cout << "查询到快递：\n";
						std::cout << package;
					}
				}
				else {
					std::cout << "-----------------------------\n\n";
					std::cout << "未查询到相关信息：\n";

				}

				std::cout << "-----------------------------\n\n";
				system("pause");

			}
			else if (query.length() <= 4) {
				system("cls");
				std::vector<Package> packageFind = packageShelf.PackageSearchID(query);
				if (packageFind.empty() == false) {
					for (auto package : packageFind) {
						std::cout << "-----------------------------\n\n";
						std::cout << "查询到快递：\n";
						std::cout << package;
					}
				}
				else {
					std::cout << "-----------------------------\n\n";
					std::cout << "未查询到相关信息：\n";

				}
				system("pause");
			}
			break;
		}
		case'q': {
			system("cls");
			fileOut.close();
			personInput.close();
			exit(EXIT_SUCCESS);
			break;
		}
		default: {
			break;
		}

		}
		++date;
		system("cls");

	} while (true);



	return EXIT_SUCCESS;
}


