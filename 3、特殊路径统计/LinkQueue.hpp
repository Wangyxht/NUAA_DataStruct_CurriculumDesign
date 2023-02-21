#ifndef LINK_QUEUE_HPP
#define LINK_QUEUE_HPP

#include<iostream>
using namespace std;
#define OK 1

template<class T>
struct queueNode {
	T data;
	struct queueNode<T>* next;
};

template<class T>
using QNode = struct queueNode<T>;
template<class T>
using LQueue = struct queueNode<T>*;
using status = int;

template<class T>
class LinkQueue {
private:
	QNode<T>* front;//头指针
	QNode<T>* rear;//尾指针
public:
	LinkQueue();//构造队列
	~LinkQueue();//销毁队列
	LinkQueue(const LinkQueue<T>& queue);//复制构造函数
	LinkQueue<T>& operator=(const LinkQueue<T>& queue);//重载赋值运算符

	status ClearQueue();//清空队列
	bool QueueEmpty() const;//判空
	int QueueLength() const;//返回长度
	T GetHead() const;//取队列头
	status GetHead(T& element);
	status QueueTraverse();//遍历队列
	status EnQueue(const T element);//入队
	status DeQueue(T& element);//出队
	status DeQueue();
};

template<class T>
LinkQueue<T>::LinkQueue(){
	try {
		front = rear = new QNode<T>;
		front->next = nullptr;
	}
	catch (bad_alloc &e) {
		cout << e.what();
		exit(EXIT_FAILURE);
	}
}

template<class T>
LinkQueue<T>::~LinkQueue(){
	QNode<T>* p = front->next;
	while (p) {
		QNode<T>* q = p;
		p = p->next;
		delete q;
	}
	delete front;
	front = rear = nullptr;

}

template<class T>
LinkQueue<T>::LinkQueue(const LinkQueue<T>& queue){
	try {
		front = rear = new QNode<T>;
		front->next = nullptr;
		for (QNode<T>* p1 = queue.front->next, *q1 = front; p1; p1 = p1->next) {
			QNode<T>* q2 = new QNode<T>;
			q2->next = nullptr;
			q2->data = p1->data;
			q1->next = q2;
			q1 = q1->next;
			if (p1->next == nullptr) rear = q1;
		}
	}
	catch (bad_alloc& e) {
		cout << e.what();
		exit(EXIT_FAILURE);
	}
}

template<class T>
LinkQueue<T>& LinkQueue<T>::operator=(const LinkQueue<T>& queue){
	if (this == &queue) {
		return *this;
	}
	try {
		front = rear = new QNode<T>;
		front->next = nullptr;
		for (QNode<T>* p1 = queue.front->next, *q1 = front; p1; p1 = p1->next) {
			QNode<T>* q2 = new QNode<T>;
			q2->next = nullptr;
			q2->data = p1->data;
			q1->next = q2;
			q1 = q1->next;
			if (p1->next == nullptr) rear = q1;
		}

		return *this;
	}
	catch (bad_alloc& e) {
		cout << e.what();
		exit(EXIT_FAILURE);
	}
}

template<class T>
status LinkQueue<T>::ClearQueue()
{
	QNode<T>* p = front->next;
	while(p){
		QNode<T>* q = p;
		p = p->next;
		delete q;
	}
	rear = front;
	return OK;
}

template<class T>
inline bool LinkQueue<T>::QueueEmpty()const
{
	return rear == front ? true : false;
}

template<class T>
int LinkQueue<T>::QueueLength()const
{
	int len = 0;
	for (QNode<T>* p = front->next; p; p = p->next) {
		++len;
	}
	return len;
}

template<class T>
inline T LinkQueue<T>::GetHead()const
{
	return front->next->data;
}

template<class T>
status LinkQueue<T>::GetHead(T& element)
{
	if (QueueEmpty()) return false;
	element = front->next->data;
	return OK;
}

template<class T>
status LinkQueue<T>::QueueTraverse()
{
	for (QNode<T>* p = front->next; p; p = p->next) {
		cout << p->data << ' ';
	}
	cout << endl;
	return OK;
}

template<class T>
status LinkQueue<T>::EnQueue(const T element)
{
	try{
		QNode<T>* s= new QNode<T>;
		s->data = element;
		s->next = nullptr;

		rear->next = s;
		rear = rear->next;	
		return OK;
	}
	catch(bad_alloc & e) {
		cout << e.what();
		exit(EXIT_FAILURE);
	}


	
}

template<class T>
status LinkQueue<T>::DeQueue(T& element)
{

	if (QueueEmpty()) return false;
	QNode<T>* p = front->next;
	element = p->data;
	if (front->next == rear) rear = front;
	front->next = p->next;
	delete p;
	return OK;
}

template<class T>
status LinkQueue<T>::DeQueue()
{
	if (QueueEmpty()) return false;
	QNode<T>* p = front->next;
	if (front->next == rear) rear = front;
	front->next = p->next;
	delete p;
	return OK;
}

#endif
