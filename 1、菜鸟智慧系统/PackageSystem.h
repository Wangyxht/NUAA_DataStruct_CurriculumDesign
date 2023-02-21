#ifndef PACKAGE_SYSTEM_H
#define PACKAGE_SYSTEM_H

#include<iostream>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<random>
#include<ctime>
#include"Package.h"
#include"Person.h"
#include"Shelf.h"
#include"Date.h"
#include"LinkList.hpp"

//系统主菜单
char systemMenu();
//查询菜单
std::string QueryMenu();
//读取人名和电话
std::vector<Person> ReadPerson(std::ifstream &fileIn);
//随机快递入站
void RandomGeneratedPackages(Shelf& shelf, std::vector<Person> &addressBook,Date date,std::ofstream& fileOut);
//随机取走快递
void RandomCollectPackages(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut);
//天数加一并且清除滞留件
void RefreshPackage(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut);

#endif // !PACKAGE_SYSTEM_H



