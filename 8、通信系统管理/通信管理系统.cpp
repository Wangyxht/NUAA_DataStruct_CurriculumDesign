#include<iostream>
#include<map>
#include<set>
#include<vector>

#define MAX_NUM 100005

struct CommunicationNode {
	long long amount;//ͨ�Ŷ��
	int target;//ͨ��Ŀ��

	CommunicationNode(long long amount, int target) :amount(amount), target(target) {};
	bool operator<(const CommunicationNode& node) const {
		if (amount == node.amount) {//�����ͬ�����С��ǰ(set�н�С����ǰ��
			return target < node.target ? true : false;
		}
		
		else {//�Ƚ϶��,��ȴ����ǰ
			return amount > node.amount ? true : false;
		}

	}
};

struct AmountInf {
	int u;//����Ľڵ�u��v
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
	//ԭ����ͨ�ŶԻ�µ�����ȥ
	IsolateNum -= IsIsolate(Set, u);
	CpairNum -= IsCPair(Set, u);


	//����ͨ�Ŷ��
	CommunicationNode pre_Node{ pre_Amount,v }; 
	Set[u].erase(pre_Node);
	Set[u].emplace( amountSave[{u, v}], v );

	//����ͨ�ŶԻ�µ�
	IsolateNum += IsIsolate(Set, u);
	CpairNum += IsCPair(Set, u);
}

std::set<CommunicationNode> Set[MAX_NUM];
std::map<std::pair<int, int>, long long> amountSave;//��ǰ��Ӧͨ�Ŷ�Ȳ�ѯ
std::vector<AmountInf> amountCancled[MAX_NUM];//�ڶ��ȡ������ȡ����ѯ

int main(int argc, char* argv[]) {

	std::ios::sync_with_stdio(false);
	int n, m;//�豸����n ����m
	std::cin >> n >> m;

	int IsolateNum = n;
	int CpairNum = 0;

	for (int i = 1; i <= m; ++i) {
		//���ڶ��ɾ��
		for (int j = 0; j < amountCancled[i].size(); ++j) {
			AddAmount(Set, amountSave, amountCancled[i][j].u, amountCancled[i][j].v, -(amountCancled[i][j].x), IsolateNum, CpairNum);
			AddAmount(Set, amountSave, amountCancled[i][j].v, amountCancled[i][j].u, -(amountCancled[i][j].x), IsolateNum, CpairNum);
		}
		
		int k;//������Ŀ
		std::cin >> k;
		for (int j = 1; j <= k; ++j) {
			int u, v, x, y;//ͨ�Ŷ���������
			std::cin >> u >> v >> x >> y;
			if (i + y <= m) {
				amountCancled[i + y].emplace_back(u,v,x);//ͨ�Ŷ�ȹ���ʱ�䱣��
			}
			AddAmount(Set, amountSave, u, v, x ,IsolateNum, CpairNum);
			AddAmount(Set, amountSave, v, u, x, IsolateNum, CpairNum);
		}

		int l;//ͨ����Ҫ�����ѯ����
		std::cin >> l;
		//��ѯͨ����Ҫ����
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

		int p;//ͨ�ŶԲ�ѯ
		int q;//ͨ�Źµ���ѯ

		std::cin >> p >> q;
		//ͨ�Źµ���ѯ
		if (p == 1) {
			std::cout << IsolateNum << '\n';
		}
		//ͨ�ŶԲ�ѯ
		if (q == 1) {
			std::cout << CpairNum << '\n';
		}
	}


	return EXIT_SUCCESS;
}
