#ifndef SqList_HPP
#define SqList_HPP
#include<iostream>

#define INIT_SIZE 100
#define INCREAMENT 10
#define OK 1; 
using namespace std;
using status = int;


template<class T>
class SqList {
private:
	T* data;
	int length;
	int size;

public:
	SqList();//��������Ա�L
	~SqList();//�������Ա�L
	inline T* GetList();
	status ClearList();//����Ϊ�ձ�
	status CreatList();//�������Ա�
	bool ListEmpty() const;//���Ա��Ƿ�Ϊ��
	int ListLength() const;//��ĳ���
	status GetElemet(int i, T& element);//��ȡ��i��Ԫ��
	int LocateElement(T element) const;
	status PriorElement(T cur_element, T& pre_element);//��ȡǰ��
	status NextElement(T cur_element, T& next_element);//��ȡ���
	status ListTraverse();//�������Ԫ��
	status SetElement(int i, T element);//���õ�i��Ԫ��Ϊe
	status InsertElement(int i, T element);//�ڵ�i��λ�ò���Ԫ��
	status DeleteElement(int i, T& element);//�ڵ�i��λ��ɾ�� 
	status DeleteElement(int i);

	T& operator[](int i);

};

template<class T>
SqList<T>::SqList() {
	try {
		data = new T[INIT_SIZE];
		size = INIT_SIZE;
		length = 0;
	}
	catch (bad_alloc& error) {
		cout << error.what() << endl;
		exit(EXIT_FAILURE);
	}

}

template<class T>
SqList<T>::~SqList() {
	size = length = 0;
	delete[] data;
}

template<class T>
inline T* SqList<T>::GetList()
{
	return data;
}

template<class T>
status SqList<T>::CreatList() {
	int len;
	cout << "Please enter the number of elements:";
	cin >> len;
	if (len < 0) return false;

	cout << "Please enter elements:";
	for (int i = 0; i < len; ++i) {
		T element;
		cin >> element;
		InsertElement(i+1, element);
	}

	length = len;
	return OK;
}

template<class T>
status SqList<T>::ClearList() {
	length = 0;
	return OK;
}

template<class T>
bool SqList<T>::ListEmpty() const {
	if (length == 0) return true;
	else return false;
}

template<class T>
int SqList<T>::ListLength() const {
	return length;
}

template<class T>
status SqList<T>::GetElemet(int i, T& element) {
	if (i<1 || i>size) return 0;
	element = data[i - 1];

	return OK;
}

template<class T>
int SqList<T>::LocateElement(T element) const {
	for (int i = 0; i < length; ++i) {
		if (element == data[i]) return i + 1;
	}

	return -1;
}

template<class T>
status SqList<T>::PriorElement(T cur_element, T& pre_element) {
	for (int i = 0; i < length; ++i) {
		if (data[i] == cur_element && i != 0) {
			pre_element = data[i - 1];
			return OK
		}
	}
	return 0;
}

template<class T>
status SqList<T>::NextElement(T cur_element, T& next_element) {
	for (int i = 0; i < length; ++i) {
		if (data[i] == cur_element && i != length - 1) {
			next_element = data[i + 1];
			return OK;
		}
	}

	return 0;
}

template<class T>
status SqList<T>::ListTraverse() {
	for (int i = 1; i <= length; ++i) {
		int element;
		GetElemet(i, element);
		cout << element << " ";
	}
	cout << endl;
	return OK;
}

template<class T>
status SqList<T>::SetElement(int i, T element)
{
	data[i - 1] = element;
	return OK;
}

template<class T>
status SqList<T>::InsertElement(int i, T element) {
	if (i<1 || i>length + 1) return 0;

	if (length + 1 >= size) {//�������鳤�����·���
		try {		 
			T* newBase = new T[length + INCREAMENT];
			for (int j = 0; j < length; ++j) {
				newBase[j] = data[j];
			}
			delete[] data;
			data = newBase;
			size += INCREAMENT;
		}
		catch (bad_alloc& error) {
			cout << error.what() << endl;
			exit(EXIT_FAILURE);
		}
	}

	for (int j = length; j > i - 1; --j) {
		data[j] = data[j - 1];
	}
	data[i - 1] = element;
	length++;
	return OK;

}

template<class T>
status SqList<T>::DeleteElement(int i, T& element) {
	if (i<1 || i>length) return 0;
	
	for (int j = i; j < length; ++j) {
		element = data[j - 1];
		data[j - 1] = data[j];
	}
	length--;
	return OK;
}

template<class T>
status SqList<T>::DeleteElement(int i){
	if (i<1 || i>length) return 0;

	for (int j = i; j < length; ++j) {
		data[j - 1] = data[j];
	}
	length--;
	return OK;
}

template<class T>
inline T& SqList<T>::operator[](int i) {
	return data[i];
}

#endif // !SqList_HPP
