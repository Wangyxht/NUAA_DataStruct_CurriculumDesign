#include<iostream>
#include<map>
#include<set>
#include<vector>

#define MAX_NUM 100005

struct CommunicationNode {
	long long amount;//通信额度
	int target;//通信目标

	CommunicationNode(long long amount, int target) :amount(amount), target(target) {};
	bool operator<(const CommunicationNode& node) const {
		if (amount == node.amount) {//额度相同，标号小在前(set中较小者在前）
			return target < node.target ? true : false;
		}
		
		else {//比较额度,额度大的在前
			return amount > node.amount ? true : false;
		}

	}
};

struct AmountInf {
	int u;//申请的节点u和v
	int v;
	long long x;

	AmountInf(int u, int v, int x) :u(u), v(v), x(x) {};
};

bool IsIsolate(std::set<CommunicationNode> Set[], int u) {
	if (Set[u].begin() == Set[u].end() || Set[u].begin()->amount == 0) return true;
	else return false;
}

bool IsCPair(std::set<CommunicationNode> Set[], int u) {
	if (IsIsolate(Set, u)) return false;
	int v = Set[u].begin()->target;
	if (!IsIsolate(Set, v) && Set[v].begin()->target == u) return true;
	else return false;
}

void AddAmount(std::set<CommunicationNode> Set[] ,std::map<std::pair<int, int>, long long> &amountSave, int u,int v, long long x, int &IsolateNum, int &CpairNum) {
	long long pre_Amount = amountSave[{u, v}];
	amountSave[{u, v}] += x;
	//原来是通信对或孤岛先抛去
	IsolateNum -= IsIsolate(Set, u);
	CpairNum -= IsCPair(Set, u);


	//更新通信额度
	CommunicationNode pre_Node{ pre_Amount,v }; 
	Set[u].erase(pre_Node);
	Set[u].emplace( amountSave[{u, v}], v );

	//更新通信对或孤岛
	IsolateNum += IsIsolate(Set, u);
	CpairNum += IsCPair(Set, u);
}

std::set<CommunicationNode> Set[MAX_NUM];
std::map<std::pair<int, int>, long long> amountSave;//当前对应通信额度查询
std::vector<AmountInf> amountCancled[MAX_NUM];//在额度取消天数取消查询

int main(int argc, char* argv[]) {

	std::ios::sync_with_stdio(false);
	int n, m;//设备数量n 天数m
	std::cin >> n >> m;

	int IsolateNum = n;
	int CpairNum = 0;

	for (int i = 1; i <= m; ++i) {
		//过期额度删减
		for (int j = 0; j < amountCancled[i].size(); ++j) {
			AddAmount(Set, amountSave, amountCancled[i][j].u, amountCancled[i][j].v, -(amountCancled[i][j].x), IsolateNum, CpairNum);
			AddAmount(Set, amountSave, amountCancled[i][j].v, amountCancled[i][j].u, -(amountCancled[i][j].x), IsolateNum, CpairNum);
		}
		
		int k;//申请数目
		std::cin >> k;
		for (int j = 1; j <= k; ++j) {
			int u, v, x, y;//通信额度申请变量
			std::cin >> u >> v >> x >> y;
			if (i + y <= m) {
				amountCancled[i + y].emplace_back(u,v,x);//通信额度过期时间保存
			}
			AddAmount(Set, amountSave, u, v, x ,IsolateNum, CpairNum);
			AddAmount(Set, amountSave, v, u, x, IsolateNum, CpairNum);
		}

		int l;//通信主要对象查询数量
		std::cin >> l;
		//查询通信主要对象
		for (int j = 1; j <= l; ++j) {
			int checkTarget;
			std::cin >> checkTarget;
			if (IsIsolate(Set,checkTarget)) {
				std::cout << 0 << '\n';
			}
			else {
				std::cout << Set[checkTarget].begin()->target << '\n';
			}
		}

		int p;//通信对查询
		int q;//通信孤岛查询

		std::cin >> p >> q;
		//通信孤岛查询
		if (p == 1) {
			std::cout << IsolateNum << '\n';
		}
		//通信对查询
		if (q == 1) {
			std::cout << CpairNum << '\n';
		}
	}


	return EXIT_SUCCESS;
}
