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
	os << "包裹ID：" << package.ID << '\n';
	if (package.size == SMALL) {
		os << "尺寸：小型\n";
	}
	else if (package.size == MEDIUM) {
		os << "尺寸：中型\n";
	}
	else {
		os << "尺寸：大型\n";
	}
	os << "收件人信息:\n" << package.addressee;
	
	
	return os;
}
