#ifndef PACKAGE_H_
#define PACKAGE_H_
#include<iostream>
#include"Person.h"
#include"Date.h"

#define LARGE 3
#define MEDIUM 2
#define SMALL 1

class Package
{
private:
	std::string ID;
	unsigned short size;
	Date arriveDate;
	Person addressee;
	unsigned short dayIn = 0;

public:
	
	Package() {};
	Package(int size_,Date arriveDate_, Person addressee_ ):size(size_),arriveDate(arriveDate_), addressee(addressee_), dayIn(0){};
	unsigned short PackageSize();
	void CreateID(int i);
	std::string GetID();
	Person Addressee();
	unsigned short& DayIn();

	friend std::ostream& operator<<(std::ostream& os,const Package& package);

};


#endif // !PACKAGE_H_


