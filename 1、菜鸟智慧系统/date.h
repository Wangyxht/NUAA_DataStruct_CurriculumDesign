#pragma once
#include<iostream>
#include<string>

class Date
{
private:
	int year;
	int month;
	int day;

public:
	Date() {};
	Date(int year_, int month_, int day_) :year(year_), month(month_), day(day_) {};

	std::string GetDateString();
	void operator++();

	friend std::ostream& operator<<(std::ostream& os,const Date &date);

};

