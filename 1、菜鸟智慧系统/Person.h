#ifndef PERSON_H_
#define PERSON_H_
#include<iostream>

class Person
{
private:
	std::string name;
	std::string tele;
	static const int MAX_PERSON = 30;
	bool has_package = false;

public:
	Person() {};
	Person(std::string name_, std::string tele_) :name(name_), tele(tele_) {};

	std::string Name();
	std::string Phone();

	void PackageCome();
	void PackageCollect();
	bool HasPackage();
	
	
	bool operator==(const Person& person);
	friend std::ostream& operator<<(std::ostream& os, const Person& person);
	
};

#endif // !PERSON_H_



