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

	int GetLeastID(int size);//�ҵ���С�Ŀձ��
	int Capability(int size);
	void PackageIn(Package& package);//�ϼܰ���
	std::vector<Package> PackageSearchPhone(std::string);
	std::vector<Package> PackageSearchID(std::string);
	std::vector<Package> PackageRefresh();//ˢ�¿�ݻ���
	std::vector<Package> PackageCollect(Person& person);//ĳ��ȡ����
	int ShowPackageReturn_Weekly();
	void WeeklyRefresh();

};


#endif // !SHELF_H_


