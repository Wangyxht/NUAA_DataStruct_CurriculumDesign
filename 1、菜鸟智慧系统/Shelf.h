#ifndef SHELF_H_
#define SHELF_H_

#include"LinkList.hpp"
#include"Package.h"
#include<vector>
#include<cstring>

class Shelf
{
private:

	LinkList<Package> larageShelf;
	LinkList<Package> mediumShelf;
	LinkList<Package> smallShelf;

	static const int MAX_LARGE_PACKAGE = 50;
	static const int MAX_MEDIUM_PACKAGE = 100;
	static const int MAX_SMALL_PACKAGE = 500;

	std::vector<bool> LargeID;
	std::vector<bool> MediumID;
	std::vector<bool> SmallID;
	
	int packageNum = 0;
	int packageReturn_Weekly = 0;


public:

	Shelf();

	int GetLeastID(int size);//找到最小的空编号
	int Capability(int size);
	void PackageIn(Package& package);//上架包裹
	std::vector<Package> PackageSearchPhone(std::string);
	std::vector<Package> PackageSearchID(std::string);
	std::vector<Package> PackageRefresh();//刷新快递货架
	std::vector<Package> PackageCollect(Person& person);//某人取包裹
	int ShowPackageReturn_Weekly();
	void WeeklyRefresh();

};


#endif // !SHELF_H_


