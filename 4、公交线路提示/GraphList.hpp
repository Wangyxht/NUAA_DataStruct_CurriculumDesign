#ifndef GRAPH_HPP
#define GRAPH_HPP
#include"SqList.hpp"
#include<vector>

#define OK 1
using status = int;

template<class TT>
struct ArcNode {
	int adjvex;
	TT arcInf;
	struct ArcNode<TT>* nextArc;
	struct  ArcNode<TT>* preArc;
};

template<class T,class TT>
struct VexNode {
	T vexData;
	struct ArcNode<TT>* firstArc;

	VexNode():firstArc(nullptr){};
	VexNode(T data) :vexData(data), firstArc(nullptr) {};
};

template<class T, class TT>
class GraphList {
private:
	SqList<VexNode<T,TT>> vertices;
	short kind;
	int vexNum;
	int arcNum;

public:
	vector<int> visit;
	GraphList();
	//~GraphList();
	int LocateVex(const T& vexData);
	T GetVex(int vexLoc);
	ArcNode<TT>*& FirstArc(int vexLoc);
	ArcNode<TT>*& NextArc(int vexLoc, ArcNode<TT>* cur_arc);
	int VexNum();
	int VexAdjVexNum(int vexData);
	status InsertVex(const T& vexData);
	status InsetArc(const T& startVex ,const T& endVex);
	status InsetArc(const T& startVex, const T& endVex,const TT& arcInf);


};

template<class T, class TT>
GraphList<T, TT>::GraphList() {
	kind = 0;
	vexNum = arcNum = 0;
}

template<class T, class TT>
int GraphList<T, TT>::LocateVex(const T& vexData){
	for (int i = 0; i < vexNum; ++i) {
		if (vertices[i].vexData==vexData) {
			return i;
		}
	}
	return -1;
}

template<class T, class TT>
inline T GraphList<T, TT>::GetVex(int vexLoc) {
	if (vexLoc < 0 || vexLoc >= vertices.ListLength()) throw"Invalid Value";
	return vertices[vexLoc].vexData;
}

template<class T, class TT>
ArcNode<TT>*& GraphList<T, TT>::FirstArc(int vexLoc) {
	return vertices[vexLoc].firstArc;
}

template<class T, class TT>
ArcNode<TT>*& GraphList<T, TT> ::NextArc(int vexLoc, ArcNode<TT>* cur_arc) {
	return cur_arc->nextArc;
}

template<class T, class TT>
inline int GraphList<T, TT>::VexNum()
{
	return vexNum;
}

template<class T, class TT>
int GraphList<T, TT>::VexAdjVexNum(int vexLoc)
{
	int arcNum=0;
	for (ArcNode<TT>* p = vertices[vexLoc].firstArc; p; p = p->nextArc) {
		++arcNum;
	}

	return arcNum;
}

template<class T, class TT>
status GraphList<T, TT>::InsertVex(const T& vexData) {
	VexNode<T,TT> newVex(vexData);
	vertices.InsertElement(vertices.ListLength() + 1, newVex);
	vexNum++;
	visit.push_back(0);
	return OK;
}

template<class T, class TT>
status GraphList<T, TT>::InsetArc(const T& startVex ,const T& endVex)
{
	int startLoc = LocateVex(startVex);
	int endLoc = LocateVex(endVex);

	if (endLoc == -1 || startLoc == -1) return false;

	if (kind == 0) {
		if (vertices[startLoc].firstArc==nullptr) {
			vertices[startLoc].firstArc= new ArcNode<TT>;
			ArcNode<TT>* p= vertices[startLoc].firstArc;
			p->preArc = nullptr;
			p->nextArc = nullptr;
			p->adjvex = endLoc;
		}
		else {
			ArcNode<TT>* p = vertices[startLoc].firstArc;
			while (p->nextArc) {
				p = p->nextArc;
			}
			p->nextArc = new ArcNode<TT>;
			p->nextArc->preArc = p;
			p = p->nextArc;
			p->nextArc = nullptr;
			p->adjvex = endLoc;
		}
		

		if (vertices[endLoc].firstArc == nullptr) {
			vertices[endLoc].firstArc= new ArcNode<TT>;
			ArcNode<TT>* q = vertices[endLoc].firstArc;
			q->preArc = nullptr;
			q->nextArc = nullptr;
			q->adjvex = startLoc;
			
		}
		else {
			ArcNode<TT>* q = vertices[endLoc].firstArc;
			while (q->nextArc) {
				q = q->nextArc;
			}
			q->nextArc = new ArcNode<TT>;
			q->nextArc->preArc = q;
			q = q->nextArc;
			q->nextArc = nullptr;
			q->adjvex = startLoc;
		}

	}

	arcNum++;
	return OK;
}

template<class T, class TT>
status GraphList<T, TT>::InsetArc(const T& startVex, const T& endVex ,const TT& arcInf)
{
	int startLoc = LocateVex(startVex);
	int endLoc = LocateVex(endVex);

	if (endLoc == -1 || startLoc == -1) return false;

	if (kind == 0) {
		if (vertices[startLoc].firstArc == nullptr) {
			vertices[startLoc].firstArc = new ArcNode<TT>;
			ArcNode<TT>* p = vertices[startLoc].firstArc;
			p->preArc = nullptr;
			p->nextArc = nullptr;
			p->adjvex = endLoc;
			p->arcInf = arcInf;
		}
		else {
			ArcNode<TT>* p = vertices[startLoc].firstArc;
			while (p->nextArc) {
				p = p->nextArc;
			}
			p->nextArc = new ArcNode<TT>;
			p->nextArc->preArc = p;
			p = p->nextArc;
			p->nextArc = nullptr;
			p->adjvex = endLoc;
			p->arcInf = arcInf;
		}


		if (vertices[endLoc].firstArc == nullptr) {
			vertices[endLoc].firstArc = new ArcNode<TT>;
			ArcNode<TT>* q = vertices[endLoc].firstArc;
			q->preArc = nullptr;
			q->nextArc = nullptr;
			q->adjvex = startLoc;
			q->arcInf = arcInf;

		}
		else {
			ArcNode<TT>* q = vertices[endLoc].firstArc;
			while (q->nextArc) {
				q = q->nextArc;
			}
			q->nextArc = new ArcNode<TT>;
			q->nextArc->preArc = q;
			q = q->nextArc;
			q->nextArc = nullptr;
			q->adjvex = startLoc;
			q->arcInf = arcInf;
		}

	}

	arcNum++;
	return OK;
}




#endif // !GRAPH_HPP

