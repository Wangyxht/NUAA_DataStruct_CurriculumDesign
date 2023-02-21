#ifndef LINKLIST_HPP
#define LINKLIST_HPP
#include<iostream>

#define OK 1;

template<class T>
struct Lnode {
	T data;
	Lnode<T>* next;
	Lnode<T>* pre;

	Lnode() :next(nullptr), pre(nullptr) {};
};

template<class T>
using LNode = Lnode<T>;

template<class T>
using Linklist = Lnode<T>*;

using status = int;

template<class T>
class LinkList {
private:
	Linklist<T> l;
public:
	LinkList();//构链表L
	~LinkList();//销毁链表L
	status ClearList();//重置为空表
	status CreateList();//建立线性表
	bool ListEmpty() const;//线性表是否为空
	int ListLength() const;//表的长度
	status GetElemet(int i, T& element);//获取第i个元素
	int LocateElement(T element) const;
	status PriorElement(T cur_element, T& pre_element);//获取前驱
	status NextElement(T cur_element, T& next_element);//获取后继
	status ListTraverse();//依次输出元素
	status SetElement(int i, T element);//设置第i个元素为e
	status InsertElement(int i, T element);//在第i个位置插入元素
	status DeleteElement(int i, T& element);//在第i个位置删除 
	status DeleteElement(int i);
	LNode<T>* operator[](int i);
	status PushBack(T &element);
};

template<class T>
LinkList<T>::LinkList() {
	try {
		l = new LNode<T>;
		l->next = nullptr;
	}
	catch (std::bad_alloc& error) {
		std::cout << error.what() << std::endl;
		exit(EXIT_FAILURE);
	}

}

template<class T>
LinkList<T>::~LinkList() {
	LNode<T>* p = l;
	while (p) {
		LNode<T>* q = p;
		p = p->next;
		delete q;
	}
	l = nullptr;
}

template<class T>
status LinkList<T>::ClearList() {
	LNode<int>* p = l->next;
	while (p) {
		LNode<T>* q = p;
		p = p->next;
		delete q;
	}
	l->next = nullptr;
	return OK;
}

template<class T>
status LinkList<T>::CreateList() {
	int len = 0;
	std::cout << "Please enter the number of elements:";
	std::cin >> len;
	if (len < 0) return false;
	std::cout << "Please enter elements:";
	for (int i = 0; i < len; ++i) {
		T element;
		std::cin >> element;
		InsertElement(i + 1, element);
	}

	return OK;

	
}

template<class T>
bool LinkList<T>::ListEmpty() const{
	if (l->next == nullptr) return true;
	else return false;
	
}

template<class T>
int LinkList<T>::ListLength() const
{
	int len = 0;
	for (LNode<T>* p = l->next; p; p = p->next) {
		++len;
	}
	return len;
}

template<class T>
status LinkList<T>::GetElemet(int i, T& element) {
	if (i<1 || i>ListLength()) return false;
	LNode<T>* p = l->next;
	for (int j = 0; j < i - 1; ++j) {
		p = p->next;
	}
	element = p->data;

	return OK;
}

template<class T>
status LinkList<T>::ListTraverse(){
	for (LNode<T>* p = l->next; p; p = p->next) {
		std::cout << p->data << " ";
	}
	std::cout << std::endl;
	return OK;
}

template<class T>
status LinkList<T>::SetElement(int i, T element){
	
	if (i<1 || i>ListLength()) return false;
	LNode<T>* p = l->next;
	for (int j = 0; j < i; ++j) {
		p = p->next;
	}
	p->data = element;
	return OK;
}

template<class T>
int LinkList<T>::LocateElement(T element) const{
	
	int location=0;
	for (LNode<T>* p = l->next; p; p = p->next) {
		if (p->data == element) return location;
		++location;

	}

	return -1;
}

template<class T>
status LinkList<T>::PriorElement(T cur_element, T& pre_element){
	for (LNode<T>* p = l->next, *q = l; p; p = p->next, q = q->next) {
		if (p->data == cur_element) {
			pre_element = q->data;
			return OK;
		}
	}

	return false;
}

template<class T>
status LinkList<T>::NextElement(T cur_element, T& next_element){
	for (LNode<T>* p = l->next, *q = l; p; p = p->next, q = q->next) {
		if (q->data == cur_element) {
			next_element = p->data;
			return OK;
		}
	}

	return false;
}

template<class T>
status LinkList<T>::InsertElement(int i, T element) {
	if (i<1 || i>ListLength() + 1) return false;
	
	LNode<T>* p = l->next, *q = l;
	for (int j = 0; j < i - 1 ; ++j) {
		p = p->next;
		q = q->next;
	}

	try {
		LNode<T>* newData = new LNode<T>;
		newData->data = element;
		newData->next = p;
		newData->pre = q;
		q->next = newData;
	}
	catch (std::bad_alloc& error) {
		std::cout << error.what();
		exit(EXIT_FAILURE);
	}

	return OK;
	
}

template<class T>
status LinkList<T>::PushBack(T &element)
{
	LNode<T>* p;
	for (p = l; p->next; p = p->next) {};
	p->next = new LNode<T>;
	p->next->pre = p;
	p = p->next;
	p->next = nullptr;
	p->data = element;

	return OK;
}

template<class T>
status LinkList<T>::DeleteElement(int i, T& element){
	if (i<1 || i>ListLength()) return false;
	LNode<T>* p = l->next;
	for (int j = 0; j < i - 1; ++j) {		
		p = p->next;
	}
	
	p->pre->next = p->next;
	delete p;
	return OK;
	
}

template<class T>
status LinkList<T>::DeleteElement(int i) {
	if (i<1 || i>ListLength()) return false;
	LNode<T>* p = l->next;
	LNode<T>* q = l;
	for (int j = 0; j < i - 1; ++j) {
		p = p->next;
		q = q->next;
	}
	q->next = p->next;
	delete p;
	return OK;

}

template<class T>
LNode<T>* LinkList<T>::operator[](int i)
{
	if (i<0 || i>ListLength() + 1) throw "Invalid";
	LNode<T>* p = l->next;
	for (int j = 0; j < i ; ++j) {
		p = p->next;
	}

	return p;
}



#endif // !LINKLIST_HPP
