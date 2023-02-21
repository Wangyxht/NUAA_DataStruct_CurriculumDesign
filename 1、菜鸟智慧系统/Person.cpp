#include "Person.h"



std::string Person::Name()
{
	return name;
}

std::string Person::Phone()
{
	return tele;
}

void Person::PackageCome()
{
	has_package = true;
}

void Person::PackageCollect()
{
	has_package = false;
}

bool Person::HasPackage()
{
	return has_package;
}

bool Person::operator==(const Person& person)
{
	if (person.name == name && person.tele == tele) {
		return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
	os << "ÐÕÃû£º" << person.name << '\n';
	os << "TEL:" << person.tele << '\n';
	return os;
}