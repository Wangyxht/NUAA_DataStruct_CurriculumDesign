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

//ϵͳ���˵�
char systemMenu();
//��ѯ�˵�
std::string QueryMenu();
//��ȡ�����͵绰
std::vector<Person> ReadPerson(std::ifstream &fileIn);
//��������վ
void RandomGeneratedPackages(Shelf& shelf, std::vector<Person> &addressBook,Date date,std::ofstream& fileOut);
//���ȡ�߿��
void RandomCollectPackages(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut);
//������һ�������������
void RefreshPackage(Shelf& shelf, std::vector<Person>& addressBook, Date date, std::ofstream& fileOut);

#endif // !PACKAGE_SYSTEM_H



