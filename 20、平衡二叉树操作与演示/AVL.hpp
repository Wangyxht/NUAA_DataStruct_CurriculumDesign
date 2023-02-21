#ifndef ASL_HPP_
#define ASL_HPP_
#include"LinkQueue.hpp"
#include<vector>
#define OK 1

#define LL 1
#define RR 2
#define LR 3
#define RL 4

template<class T>
struct BiNode {
	T data;
	struct BiNode* lchild;
	struct BiNode* rchild;
	struct BiNode* parent;
	BiNode() :lchild(nullptr), rchild(nullptr), parent(nullptr) {};
};

template<class T>
using Avl = BiNode<T>*;

using status = int;

template<class T>
class AVL {
private:
	Avl<T> tree;

	bool NodeBalance(Avl<T>& Tr);
	int NodeBalanceFactor(Avl<T>& Tr);
	int JudgeImbalanceType(Avl<T>& Tr);
	status ClearAVL();
	status ClearAVL(Avl<T>& Tr);
	status Rotate(Avl<T>& Tr, int type);
	status LeftRotate(Avl<T> Tr);
	status RightRotate(Avl<T> Tr);
	status ReBalance(Avl<T> Tr);
	int BiTreeDepth(Avl<T> Tr);

public:
	AVL() :tree(nullptr) {};//���캯��	
	~AVL();//��������

	status Insert(const T& element);
	status Delete(const T& element);
	bool Find(const T& element);

	status LevelOrderTraverse();
	status InOrderTraverse();
	status InOrderTraverse(Avl<T>& Tr);
	status DisplayAVL();



};

template<class T>
AVL<T>::~AVL()
{
	ClearAVL();
}

/***************************************************************
  *  @brief     ��ASL�������ݲ��Զ�ƽ��
  *  @param     element: ����Ŀ��
  *  @note      ��
  *  @Sample usage:     �����෽���������ݵĲ���
 **************************************************************/
template<class T>
status AVL<T>::Insert(const T& element)
{
	if (tree == nullptr) {//����ֱ�Ӳ���
		tree = new BiNode<T>;
		tree->data = element;
		tree->parent = tree;
		return OK;
	}
	else {
		BiNode<T>* p = tree;
		BiNode<T>* q = nullptr;
		bool insertLeft;
		while (p) {
			if (p->data == element) return 0;//������ͬ��ֵʱ���޷�����
			else if (p->data > element) {//����ֵ��ڵ�ȽϽ�С������Ѱ�Ҳ���λ��
				q = p;
				p = p->lchild;
				insertLeft = true;
			}
			else {//����ֵ��ڵ�ȽϽϴ�����Ѱ�Ҳ���λ��
				q = p;
				p = p->rchild;
				insertLeft = false;
			}
		}

		if (insertLeft) {//���ȷ����������
			q->lchild = new BiNode<T>;
			q->lchild->parent = q;
			q = q->lchild;
			q->data = element;
		}
		else {//ȷ�����Ҳ����
			q->rchild = new BiNode<T>;
			q->rchild->parent = q;
			q = q->rchild;
			q->data = element;
		}

		ReBalance(q);
		return OK;
	}
}

/***************************************************************
  *  @brief     ��ASLɾ�����ݲ��Զ�ƽ��
  *  @param     element: ɾ��Ŀ��
  *  @note      ��
  *  @Sample usage:     �����෽���������ݵ�ɾ��
 **************************************************************/
template<class T>
status AVL<T>::Delete(const T& element)
{
	if (tree == nullptr) return 0;//����������

	BiNode<T>* p = tree;
	BiNode<T>* q = nullptr;
	while (p && p->data != element) {//���ֵ�����
		if (p->data > element) {//����ֵ��ڵ�ȽϽ�С������Ѱ��
			q = p;
			p = p->lchild;
		}
		else if (p->data < element) {//����ֵ��ڵ�ȽϽϴ�����Ѱ��
			q = p;
			p = p->rchild;
		}
	}

	if (p == nullptr) return 0;//δ�ҵ��򷵻�
	else {//�ҵ���ֵp
		if (p->lchild == nullptr && p->rchild == nullptr) {//���ΪҶ�ڵ㣬ֱ��ɾ��
			if (q) {
				if (q->lchild == p) {
					delete p;
					q->lchild = nullptr;
				}
				else {
					delete p;
					q->rchild = nullptr;
				}
				ReBalance(q);
			}
			else {
				delete p;
				tree = nullptr;
				ReBalance(tree);
			}

		}
		else if (p->lchild == nullptr) {//���������Ϊ��
			if (q) {
				if (q->lchild == p) {
					q->lchild = p->rchild;
					p->rchild->parent = q;
					ReBalance(q);
					delete p;
				}
				else {
					q->rchild = p->rchild;
					p->rchild->parent = q;
					delete p;
					ReBalance(q);
				}

			}
			else {
				tree = p->rchild;
				delete p;
				ReBalance(tree);
			}

		}
		else if (p->rchild == nullptr) {//���������Ϊ��
			if (q) {
				if (q->lchild == p) {
					q->lchild = p->lchild;
					p->lchild->parent = q;
					delete p;
					ReBalance(q->lchild);
				}
				else {
					q->rchild = p->lchild;
					p->lchild->parent = q;
					delete p;
					ReBalance(q->rchild);
				}

			}
			else {
				tree = p->lchild;
				delete p;
				ReBalance(tree);
			}

		}
		else {//�������Ϊ�գ��������������ҽڵ㲹��
			BiNode<T>* t = p->lchild;//tΪp������
			BiNode<T>* s = nullptr;
			while (t->rchild) {//Ѱ�����ҽڵ�t��sΪ�丸�ڵ�
				s = t;
				t = t->rchild;
			}
			p->data = t->data;

			if (s) {//����������
				if (t->lchild == nullptr && t->rchild == nullptr) {//���ҽڵ㲻����������
					s->rchild = t->rchild;
					delete t;
					ReBalance(s);
				}
				else {//���ҽڵ������������
					s->rchild = t->lchild;
					t->lchild->parent = s;
					delete t;
					ReBalance(s);
				}
			}
			else {//������������
				p->lchild = t->lchild;
				if (p->rchild) p->rchild->parent = t;
				delete t;
				ReBalance(p);
			}



		}
	}

	return OK;

}

/***************************************************************
  *  @brief     ��ASL����ĳ������
  *  @param     element: ����Ŀ��
  *  @note      ��
  *  @Sample usage:     �����෽���������ݵĲ���
 **************************************************************/
template<class T>
bool AVL<T>::Find(const T& element)
{
	if (tree == nullptr) return false;

	BiNode<T>* p = tree;
	while (p && p->data != element) {
		if (p->data > element) {
			p = p->lchild;
		}
		else if (p->data < element) {
			p = p->rchild;
		}
	}

	return p != nullptr;
}

template<class T>
status AVL<T>::LevelOrderTraverse()
{

	LinkQueue<BiNode<T>*> queue;
	queue.EnQueue(tree);
	queue.EnQueue(nullptr);
	while (!queue.QueueEmpty()) {
		BiNode<T>* temp = nullptr;
		queue.DeQueue(temp);

		if (temp == nullptr) {
			std::cout << "\n";
			if (queue.QueueEmpty()) break;
			queue.EnQueue(nullptr);
			continue;

		}
		else {
			std::cout << temp->data << " ";
			if (temp->lchild != nullptr) queue.EnQueue(temp->lchild);
			if (temp->rchild != nullptr) queue.EnQueue(temp->rchild);

		}

	}
	return OK;
}

template<class T>
status AVL<T>::InOrderTraverse()
{
	return InOrderTraverse(tree);
}

template<class T>
status AVL<T>::InOrderTraverse(Avl<T>& Tr)
{
	if (Tr == nullptr) {
		return false;
	}
	else {
		InOrderTraverse(Tr->lchild);
		std::cout << Tr->data << ' ';
		InOrderTraverse(Tr->rchild);
		return OK;
	}
}

/***************************************************************
  *  @brief     �ڿ���̨���������ͼ�λ���ASL
  *  @param		��
  *  @note      ֻ����ʾ0��99999��������ֵ����ʾ��δ�������������뷶Χֵ
  *  @Sample usage:     �����෽��������ʾ������
 **************************************************************/
template<class T>
status AVL<T>::DisplayAVL()
{
	static const int EMPTY = INT_MIN;
	LinkQueue<BiNode<T>*> queue;
	std::vector<T> elements;
	elements.emplace_back(tree->data);
	queue.EnQueue(tree);
	int count = 0;
	int depth = BiTreeDepth(tree);
	while (queue.QueueEmpty() == false) {
		BiNode<T>* temp;
		queue.DeQueue(temp);
		if (temp == nullptr && count <= (1 << depth) - (1 << (depth - 1))) {
			elements.emplace_back(EMPTY);
			elements.emplace_back(EMPTY);
			++count;
		}
		else if (temp != nullptr) {
			if (temp->lchild) {
				queue.EnQueue(temp->lchild);
				elements.emplace_back(temp->lchild->data);
			}
			else {
				queue.EnQueue(temp->lchild);
				elements.emplace_back(EMPTY);
			}

			if (temp->rchild) {
				queue.EnQueue(temp->rchild);
				elements.emplace_back(temp->rchild->data);
			}
			else {
				queue.EnQueue(temp->rchild);
				elements.emplace_back(EMPTY);
			}
			++count;
		}

	}


	//while (elements.size() < (1 << depth) - 1) elements.emplace_back(EMPTY);

	int display = 0;
	for (int i = 0; i < depth; ++i) {
		int loc = 1 << (depth - i + 1);
		if (i == 0) {
			printf("%*c\n", loc, '_');
		}
		else {
			for (int j = 0; j < 1 << (i - 1); j++) {
				printf("%*c", loc + 1, ' ');
				for (int k = 0; k < loc - 3; k++) printf("_");
				printf("/ \\");
				for (int k = 0; k < loc - 3; k++) printf("_");
				printf("%*c", loc + 2, ' ');
			}
			printf("\n");
			for (int j = 0; j < 1 << (i - 1); j++) {
				printf("%*c/%*c_%*c", loc, '_', loc * 2 - 2, '\\', loc, ' ');
			}
			printf("\n");
		}

		for (int j = 0; j < 1 << i; j++) {
			//printf("%*c_)%*c", loc - 1, '(', loc - 1, ' ');
			printf("%*c", loc - 3, '(');
			if (elements[display] == EMPTY) std::cout << "  X  ";
			else {
				if (0 <= elements[display] && elements[display] <= 9) std::cout << "  " << elements[display] << "  ";
				else if (10 <= elements[display] && elements[display] <= 99)std::cout << " " << elements[display] << "  ";
				else if (100 <= elements[display] && elements[display] <= 999)std::cout << " " << elements[display] << " ";
				else if (1000 <= elements[display] && elements[display] <= 9999)std::cout << "" << elements[display] << " ";
				else if (10000 <= elements[display] && elements[display] <= 99999)std::cout << "" << elements[display] << "";
			}

			++display;
			printf(")%*c", loc - 3, ' ');
		}
		printf("\n");

	}

	return OK;
}

template<class T>
int AVL<T>::BiTreeDepth(Avl<T> Tr)
{
	if (Tr == nullptr) return 0;
	else {
		int leftDepth, rightDepth;
		leftDepth = BiTreeDepth(Tr->lchild);
		rightDepth = BiTreeDepth(Tr->rchild);
		return std::max(leftDepth, rightDepth) + 1;
	}
}

/***************************************************************
  *  @brief     �жϽڵ��Ƿ�ʧ��
  *  @param     Tr ���ڵ�
  *  @note      �����Ƿ�ʧ��Ĳ���ֵ
  *  @Sample usage:     ��
 **************************************************************/
template<class T>
bool AVL<T>::NodeBalance(Avl<T>& Tr)
{
	if (Tr == nullptr) return true;
	int leftDepth = BiTreeDepth(Tr->lchild);
	int rightDepth = BiTreeDepth(Tr->rchild);
	if (abs(leftDepth - rightDepth) >= 2) return false;
	else return true;
}

template<class T>
int AVL<T>::NodeBalanceFactor(Avl<T>& Tr)
{
	if (Tr == nullptr) return 0;
	int leftDepth = BiTreeDepth(Tr->lchild);
	int rightDepth = BiTreeDepth(Tr->rchild);
	return leftDepth - rightDepth;
}

/***************************************************************
  *  @brief     ��ʧ��Ľڵ���������ж�
  *  @param     Tr ���ڵ�
  *  @note      ����LL RR LR RL��Ӧ��ֵ
  *  @Sample usage:     ��
 **************************************************************/
template<class T>
int AVL<T>::JudgeImbalanceType(Avl<T>& Tr)
{
	int rootBF = NodeBalanceFactor(Tr);
	int lchildBF = NodeBalanceFactor(Tr->lchild);
	int rchildBF = NodeBalanceFactor(Tr->rchild);

	if (rootBF > 1) {
		if (lchildBF > 0) return LL;
		else if (lchildBF <= 0) return LR;
	}
	else if (rootBF < -1) {
		if (rchildBF > 0) return RL;
		else if (rchildBF <= 0) return RR;
	}
	return -1;
}

/***************************************************************
  *  @brief     ��ʧ��Ľڵ������������
  *  @param     Tr ���ڵ�
  *  @note      ����status
  *  @Sample usage:     ��
 **************************************************************/
template<class T>
status AVL<T>::LeftRotate(Avl<T> Tr)
{
	Avl<T> rchild = Tr->rchild;//���ڵ��Һ���
	Avl<T> lchild = Tr->lchild;//���ڵ�����
	Tr->rchild = rchild->lchild;//���ڵ��Һ��ӵ����������������ڵ��������
	if (rchild->lchild != nullptr) rchild->lchild->parent = Tr;
	rchild->lchild = Tr;//���ڵ�������Һ��ӵ�����
	if (Tr != tree) {//���������λ�ò�������
		rchild->parent = Tr->parent;
		if (Tr->parent->lchild == Tr) {
			Tr->parent->lchild = rchild;
		}
		else if (Tr->parent->rchild == Tr) {
			Tr->parent->rchild = rchild;
		}
		Tr->parent = rchild;
	}
	else { //���������λ��������
		tree = rchild;
		rchild->parent = rchild;
		Tr->parent = rchild;
	}
	return OK;
}

/***************************************************************
  *  @brief     ��ʧ��Ľڵ������������
  *  @param     Tr ���ڵ�
  *  @note      ����status
  *  @Sample usage:     ��
 **************************************************************/
template<class T>
status AVL<T>::RightRotate(Avl<T> Tr)
{
	Avl<T> rchild = Tr->rchild;//���ڵ��Һ���
	Avl<T> lchild = Tr->lchild;//���ڵ�����
	Tr->lchild = lchild->rchild;//���ڵ����ӵ����������������ڵ��������
	if (lchild->rchild != nullptr) lchild->rchild->parent = Tr;
	lchild->rchild = Tr;//���ڵ���������ӵ��Һ���
	if (Tr != tree) {//���������λ�ò�������
		lchild->parent = Tr->parent;
		if (Tr->parent->lchild == Tr) {
			Tr->parent->lchild = lchild;
		}
		else if (Tr->parent->rchild == Tr) {
			Tr->parent->rchild = lchild;
		}
		Tr->parent = lchild;
	}
	else { //���������λ��������
		tree = lchild;
		Tr->parent = lchild;
		lchild->parent = lchild;
	}

	return OK;
}

/***************************************************************
  *  @brief     ��ʧ��Ľڵ㰴��ʧ��������ת
  *  @param     Tr ���ڵ� type ʧ������
  *  @note      ����status
  *  @Sample usage:     ��
 **************************************************************/
template<class T>
status AVL<T>::Rotate(Avl<T>& Tr, int type)
{
	switch (type) {
	case LL:
		RightRotate(Tr);
		break;
	case RR:
		LeftRotate(Tr);
		break;
	case LR:
		LeftRotate(Tr->lchild);
		RightRotate(Tr);
		break;
	case RL:
		RightRotate(Tr->rchild);
		LeftRotate(Tr);
		break;
	}
	return OK;
}

template<class T>
status AVL<T>::ReBalance(Avl<T> q)
{
	while (q->parent != q && abs(NodeBalanceFactor(q)) < 2) {
		q = q->parent;
	}

	if (q == tree && abs(NodeBalanceFactor(q)) < 2) return OK;
	else {
		int type = JudgeImbalanceType(q);
		Rotate(q, type);
		return OK;
	}
}

template<class T>
status AVL<T>::ClearAVL()
{
	if (tree == nullptr) return OK;
	ClearAVL(tree->lchild);
	ClearAVL(tree->rchild);
	delete tree;
	tree = nullptr;
	return 1;
}

template<class T>
status AVL<T>::ClearAVL(Avl<T>& Tr)
{
	if (Tr == nullptr) return OK;
	ClearAVL(Tr->lchild);
	ClearAVL(Tr->rchild);
	delete Tr;
	Tr = nullptr;
	return 1;
}

#endif // !ASL_HPP_