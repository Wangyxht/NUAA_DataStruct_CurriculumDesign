#include "Date.h"


void Date::operator++()
{
	if (day == 31 && month == 12) {
		year++;
		day = month = 1;
		return;
	}
	
	if (month == 2) {
		if (day == 29 && year % 4 == 0 || year % 400 == 0) {
			day = 1;
			month++;
			return;
		}
		else if (day == 28 && !(year % 4 == 0 || year % 400 == 0)) {
			day = 1;
			month++;
			return;
		}
		else {
			day++;
			return;
		}
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if (day == 31) {
			day = 1;
			month++;
			return;
		}
		else {
			day++;
			return;
		}
	}
	else {
		if (day == 30) {
			day = 1;
			month++;
			return;
		}
		else {
			day++;
			return;
		}
	}

	

}

std::string Date::GetDateString()
{
	std::string year_, month_, day_;
	
	year_ = std::to_string(year);

	if (month < 10) {
		month_ = '0'+ std::to_string(month);
	}
	else {
		month_ = std::to_string(month);
	}

	if (day < 10) {
		day_ = '0' + std::to_string(day);
	}
	else {
		day_ = std::to_string(day);
	}


	return year_ + month_ + day_;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << date.year << "Äê" << date.month << "ÔÂ" << date.day << "ÈÕ";

	return os;
}
