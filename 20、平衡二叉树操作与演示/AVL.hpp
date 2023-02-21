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
	AVL() :tree(nullptr) {};//构造函数	
	~AVL();//析构函数

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
  *  @brief     对ASL插入数据并自动平衡
  *  @param     element: 插入目标
  *  @note      无
  *  @Sample usage:     利用类方法进行数据的插入
 **************************************************************/
template<class T>
status AVL<T>::Insert(const T& element)
{
	if (tree == nullptr) {//空树直接插入
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
			if (p->data == element) return 0;//当有相同的值时，无法插入
			else if (p->data > element) {//插入值与节点比较较小，向左寻找插入位置
				q = p;
				p = p->lchild;
				insertLeft = true;
			}
			else {//插入值与节点比较较打，向右寻找插入位置
				q = p;
				p = p->rchild;
				insertLeft = false;
			}
		}

		if (insertLeft) {//如果确定在左侧插入
			q->lchild = new BiNode<T>;
			q->lchild->parent = q;
			q = q->lchild;
			q->data = element;
		}
		else {//确定在右侧插入
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
  *  @brief     对ASL删除数据并自动平衡
  *  @param     element: 删除目标
  *  @note      无
  *  @Sample usage:     利用类方法进行数据的删除
 **************************************************************/
template<class T>
status AVL<T>::Delete(const T& element)
{
	if (tree == nullptr) return 0;//空树不操作

	BiNode<T>* p = tree;
	BiNode<T>* q = nullptr;
	while (p && p->data != element) {//如果值不相等
		if (p->data > element) {//插入值与节点比较较小，向左寻找
			q = p;
			p = p->lchild;
		}
		else if (p->data < element) {//插入值与节点比较较大，向右寻找
			q = p;
			p = p->rchild;
		}
	}

	if (p == nullptr) return 0;//未找到则返回
	else {//找到该值p
		if (p->lchild == nullptr && p->rchild == nullptr) {//如果为叶节点，直接删除
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
		else if (p->lchild == nullptr) {//如果左子树为空
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
		else if (p->rchild == nullptr) {//如果右子树为空
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
		else {//如果均不为空，找左子树的最右节点补齐
			BiNode<T>* t = p->lchild;//t为p的左孩子
			BiNode<T>* s = nullptr;
			while (t->rchild) {//寻找最右节点t，s为其父节点
				s = t;
				t = t->rchild;
			}
			p->data = t->data;

			if (s) {//存在右子树
				if (t->lchild == nullptr && t->rchild == nullptr) {//最右节点不存在左子树
					s->rchild = t->rchild;
					delete t;
					ReBalance(s);
				}
				else {//最右节点的左子树存在
					s->rchild = t->lchild;
					t->lchild->parent = s;
					delete t;
					ReBalance(s);
				}
			}
			else {//不存在右子树
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
  *  @brief     对ASL查找某个数据
  *  @param     element: 查找目标
  *  @note      无
  *  @Sample usage:     利用类方法进行数据的查找
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
  *  @brief     在控制台输出二叉树图形化的ASL
  *  @param		无
  *  @note      只能显示0到99999的整型数值的显示，未适配其他类型与范围值
  *  @Sample usage:     利用类方法进行显示操作。
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
  *  @brief     判断节点是否失衡
  *  @param     Tr 树节点
  *  @note      返回是否失衡的布尔值
  *  @Sample usage:     无
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
  *  @brief     对失衡的节点进行类型判断
  *  @param     Tr 树节点
  *  @note      返回LL RR LR RL对应的值
  *  @Sample usage:     无
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
  *  @brief     对失衡的节点进行左旋操作
  *  @param     Tr 树节点
  *  @note      返回status
  *  @Sample usage:     无
 **************************************************************/
template<class T>
status AVL<T>::LeftRotate(Avl<T> Tr)
{
	Avl<T> rchild = Tr->rchild;//根节点右孩子
	Avl<T> lchild = Tr->lchild;//根节点左孩子
	Tr->rchild = rchild->lchild;//根节点右孩子的左子树调整到根节点的右子树
	if (rchild->lchild != nullptr) rchild->lchild->parent = Tr;
	rchild->lchild = Tr;//根节点调整到右孩子的左孩子
	if (Tr != tree) {//如果待调整位置不是树根
		rchild->parent = Tr->parent;
		if (Tr->parent->lchild == Tr) {
			Tr->parent->lchild = rchild;
		}
		else if (Tr->parent->rchild == Tr) {
			Tr->parent->rchild = rchild;
		}
		Tr->parent = rchild;
	}
	else { //如果待调整位置是树根
		tree = rchild;
		rchild->parent = rchild;
		Tr->parent = rchild;
	}
	return OK;
}

/***************************************************************
  *  @brief     对失衡的节点进行右旋操作
  *  @param     Tr 树节点
  *  @note      返回status
  *  @Sample usage:     无
 **************************************************************/
template<class T>
status AVL<T>::RightRotate(Avl<T> Tr)
{
	Avl<T> rchild = Tr->rchild;//根节点右孩子
	Avl<T> lchild = Tr->lchild;//根节点左孩子
	Tr->lchild = lchild->rchild;//根节点左孩子的有子树调整到根节点的左子树
	if (lchild->rchild != nullptr) lchild->rchild->parent = Tr;
	lchild->rchild = Tr;//根节点调整到左孩子的右孩子
	if (Tr != tree) {//如果待调整位置不是树根
		lchild->parent = Tr->parent;
		if (Tr->parent->lchild == Tr) {
			Tr->parent->lchild = lchild;
		}
		else if (Tr->parent->rchild == Tr) {
			Tr->parent->rchild = lchild;
		}
		Tr->parent = lchild;
	}
	else { //如果待调整位置是树根
		tree = lchild;
		Tr->parent = lchild;
		lchild->parent = lchild;
	}

	return OK;
}

/***************************************************************
  *  @brief     对失衡的节点按照失衡类型旋转
  *  @param     Tr 树节点 type 失衡类型
  *  @note      返回status
  *  @Sample usage:     无
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