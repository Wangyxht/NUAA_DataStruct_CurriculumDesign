#ifndef  SQ_STACK_HPP
#define SQ_STACK_HPP

#include<iostream>
using status = int;
using std::cout;
using std::endl;

#define OK 1

template<class T>
class sqStack {
private:
	T* base;
	T* top;
	const int  STACK_INCREAMENT = 10;
	const int STACK_INIT_SIZE = 100;
	int stackSize = STACK_INIT_SIZE;


public:
	sqStack();//����˳��ջ
	~sqStack();//����˳��ջ
	sqStack(const sqStack<T>& stk);//���ƹ��캯��
	sqStack<T>& operator=(const sqStack<T>& stk);//���ظ�ֵ�����

	status ClearStack();//˳��ջ�ÿ�
	bool StackEmpty();//�п�
	int StackLength();//���س���
	status GetTop(T &element);//ȡջ��Ԫ��
	T GetTop();
	status StackTraverse();//����˳��ջ
	status Push(const T element);//ѹջ
	status Pop(T &element);//��ջ
	status Pop();
	

};

template<class T>
sqStack<T>::sqStack()
{
	try {
		base = new T[STACK_INIT_SIZE];
		top = base;
	}
	catch (std::bad_alloc& e) {
		cout << e.what();
		exit(EXIT_FAILURE);
	}

}

template<class T>
sqStack<T>::~sqStack()
{
	delete[] base;
	top = base = nullptr;
}

template<class T>
sqStack<T>::sqStack(const sqStack<T>& stk)
{
	try {
		int len = (int)(stk.top - stk.base);
		base = new T[stk.stackSize +1];
		top = base + len;
		stackSize = stk.stackSize;
		for (auto p = stk.base, q = base; p != stk.top; ++p,++q) {
			*q = *p;
		}	
	}
	catch (std::bad_alloc& e) {
		std::cout << e.what();
		exit(EXIT_FAILURE);
	}

}

template<class T>
sqStack<T>& sqStack<T>::operator=(const sqStack<T>& stk)
{
	try {
		int len =(int) (stk.top-stk.base);
		if (this == &stk) return *this;
		base = new T[stk.stackSize + 1];
		top = base + len;
		stackSize = stk.stackSize;
		for (auto p = stk.base, q = base; p != stk.top; ++p, ++q) {
			*q = *p;
		}
		return *this;
	}
	catch (std::bad_alloc& e) {
		cout << e.what();
		exit(EXIT_FAILURE);
	}
}

template<class T>
status sqStack<T>::ClearStack()
{
	top = base;
	return OK;
}

template<class T>
bool sqStack<T>::StackEmpty()
{
	return top == base ? true : false;
}


template<class T>
int sqStack<T>::StackLength()
{
	return (int)(top - base);
}

template<class T>
status sqStack<T>::GetTop(T& element)
{
	if (StackEmpty()) return false;
	element = *(top - 1);
	return OK;

}

template<class T>
T sqStack<T>::GetTop()
{
	try {
		if (StackEmpty()) throw "Stack empty";
		return *(top - 1);
	}
	catch (const char* e) {
		cout << e << endl;
		exit(EXIT_FAILURE);
	}

}                                         

template<class T>
status sqStack<T>::StackTraverse()
{
	
	if (StackEmpty()) return OK;
	for (auto p = base; p != top; p++) {
		cout << *p<<" ";
	}
	cout << endl;

	return OK;
}

template<class T>
status sqStack<T>::Push(const T element)
{
	try {
		int len = StackLength();
		if (len + 1 == stackSize) {
			T* newBase = new T[stackSize + STACK_INCREAMENT];			
			for (T* p = base, *q = newBase; p != top; p++, q++) {
				*q = *p;
			}
			base = newBase;
			top = base + len;
			stackSize += STACK_INCREAMENT;
			
		}
		*top = element;
		top++;
	}
	catch (std::bad_alloc& e) {
		cout << e.what();
		exit(EXIT_FAILURE);
	}

	return OK;

}

template<class T>
status sqStack<T>::Pop(T& element)
{
	if (StackEmpty()) return false;
	--top;
	element = *top;
	return OK;
}

template<class T>
status sqStack<T>::Pop()
{
	if (StackEmpty()) return false;
	--top;
	return OK;
}

#endif // ! SQ_STACK_HPP
