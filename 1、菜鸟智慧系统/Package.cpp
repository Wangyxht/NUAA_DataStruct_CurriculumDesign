#include "Package.h"


unsigned short Package::PackageSize()
{
	return size;
}

void Package::CreateID(int i)
{
	ID = std::to_string(size) + std::to_string(i);
}

Person Package::Addressee()
{
	return addressee;
}

std::string Package::GetID()
{
	return ID;
}

unsigned short& Package::DayIn() {
	return dayIn;
}

std::ostream& operator<<(std::ostream& os,const Package& package)
{
	os << "����ID��" << package.ID << '\n';
	if (package.size == SMALL) {
		os << "�ߴ磺С��\n";
	}
	else if (package.size == MEDIUM) {
		os << "�ߴ磺����\n";
	}
	else {
		os << "�ߴ磺����\n";
	}
	os << "�ռ�����Ϣ:\n" << package.addressee;
	
	
	return os;
}
