//2020.10.09
//�б�(6) 11:35 ~ 11:41
//��Ʈ(19) 11:45 ~ 12:04
//�ڵ�(95) 13:33 ~ 14:30, 14:47 ~ 15:25 
//��(120)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include <algorithm>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

class Bridge {
public:
	int first; //��1
	int second; //��2
	double cost; // E*L*L
	Bridge(int f, int s, double c) :first(f), second(s), cost(c) {}

	bool operator < (const Bridge& b) const {
		return this->cost < b.cost;
	}
};


int tc = 1, TC;
int N;
double E;//����, ����
int cnt = 0;
vector<double> x, y;//������ x,y��ǥ
vector<Bridge> bridges; //��� ������ �ٸ�

vector<int> rootOf; //��, ��Ʈ��
vector<vector<int>> childrenOf; //��Ʈ��, �ڽļ���
double res = 0.0;

void init() {
	cnt = 0;
	x.clear();
	y.clear();
	bridges.clear();
	rootOf.clear();
	childrenOf.clear();
	res = 0;
}

double bridgeTax(int i, int j) {
	double w = x[i] - x[j];
	double h = y[i] - y[j];

	return E * (w * w + h * h);
}

int main(void) {
	input();
	scanf("%d", &TC);

	double tmp;

	for (; tc <= TC; ++tc) {
		init();
		scanf("%d", &N);
		childrenOf.resize(N*2);
		for (int i = 0; i < N; ++i) {
			scanf("%lf", &tmp);
			x.push_back(tmp);
		}
		for (int i = 0; i < N; ++i) {
			scanf("%lf", &tmp);
			y.push_back(tmp);
		}
		scanf("%lf", &E);

		for (int i = 0; i < N; ++i) {
			for (int j = i; j < N; ++j) {
				bridges.push_back(Bridge(i, j, bridgeTax(i, j)));
			}
		}

		sort(bridges.begin(), bridges.end());

		for (int i = 0; i < N; ++i) {
			rootOf.push_back(i);
			childrenOf[i].push_back(i); //��Ʈ�� i�� ����ȣ i, �ڱ� �ڽ��� ��Ʈ
		}

		for (auto br : bridges) {
			if (cnt == N - 1) { break; }
			int root1 = rootOf[br.first];
			int root2 = rootOf[br.second];

			//�� ���� ��Ʈ�� �ٸ���
			if (root1 != root2) {
				cnt++;
				res += br.cost;
				//���� - �ڽ��� ���� �ָ� ��Ʈ�� �����
				if (childrenOf[root1].size() >= childrenOf[root2].size()) {
					for (auto a : childrenOf[root2]) {
						//childrenOf[root1].assign(childrenOf[root2].begin(), childrenOf[root2].end());

						childrenOf[root1].push_back(a);
						rootOf[a] = root1;
						//��Ʈ �ٲ��ֱ�
					}
				}
				else {
					for (auto a : childrenOf[root2]) {
						childrenOf[root1].push_back(a);
						rootOf[a] = root1;
						//��Ʈ �ٲ��ֱ�
					}
				}
				//�� - �ڽ��� ���� �ָ� ��Ʈ�� �����
			}
		}

		printf("#%d %.lf\n",tc, res);


	}
	return 0;
}