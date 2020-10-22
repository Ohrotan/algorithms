//2020.10.15
//�б�(6) 21:14 ~ 21:20
//Ǯ��(18) 21:30 ~ 21:48
//�ڵ�(37) 21:56 ~ 22:33

//���� Ʋ��
//�����(26) 22:50 ~ 23:16

//��¥ �߿��Ѱ� �����!! for(auto item : vector)�� ���� ������ �� ���� �ȵȴ�.
//item�� ��ü�� �ƴ϶� ī�Ǻ��̶� �� ������ �ȵȴ�
//��(87)
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
#define nn(){printf("\n");}
#define line(){printf("-----------------\n");}
using namespace std;

class Nation {
public:
	int num;//�����ȣ = N*r + c
	int pop;//�α�
	int r;//��ġ
	int c;
	int root;//���屹
	vector<int> children;//�ڽ�
	Nation(int _num, int _pop, int _r, int _c) :num(_num), pop(_pop), r(_r), c(_c), root(_num) {
	}
};

vector<Nation> nations;

int N, L, R;
int mr[4] = { 0,0,1,-1 };
int mc[4] = { 1,-1,0,0 };

void printMap() {
	for (int i = 0; i < N * N; ++i) {
		if (i % N == 0) nn()
		printf("%6d", nations[i].pop);
		
	}
	nn()
	line()
}

bool inMap(int r, int c) {
	if (r >= 0 && c >= 0 && r < N && c < N) {
		return true;
	}
	return false;
}

//�����ȣ
void makeFed(int a, int b) {
	int roota = nations[a].root;
	int rootb = nations[b].root;
	if (nations[roota].children.size() > nations[rootb].children.size()) {
		//a���ٰ� b�� ����
		for (int num : nations[rootb].children) {
			nations[num].root = roota; //���� �ڽ� ��Ʈ �ٲ���
			nations[roota].children.push_back(num); //���ο� ��Ʈ�� �ڽ� �߰�
		}
		nations[roota].children.push_back(rootb); //��Ʈ���߰�
		nations[rootb].root = roota; //��Ʈ�� ��Ʈ �ٲ���
		nations[rootb].children.clear(); //��Ʈ�� �ڽ� 0

	}
	else {
		//b���ٰ� a�� ����
		for (int num : nations[roota].children) {
			nations[num].root = rootb; //���� �ڽ� ��Ʈ �ٲ���
			nations[rootb].children.push_back(num); //���ο� ��Ʈ�� �ڽ� �߰�
		}
		nations[rootb].children.push_back(roota);
		nations[roota].root = rootb; 
		nations[roota].children.clear(); 
	}
}

//���氳��
bool openBorder() {
	bool ret = false;
	for (int i = 0; i < N*N; ++i) {
		int r = nations[i].r;
		int c = nations[i].c;
		int nr, nc, nn;//���� ������ ��ġ, ��ȣ
		for (int j = 0; j < 4; ++j) {
			nr = r + mr[j];
			nc = c + mc[j];
			if (!inMap(nr, nc)) {
				continue;
			}
			nn = nr * N + nc;

			//�̹� ����
			if (nations[i].root == nations[nn].root) {
				continue;
			}

			//�α����� ���ǿ� ������
			int gap = abs(nations[i].pop - nations[nn].pop);
			if (gap >= L && gap <= R) {
				makeFed(i, nn);
				ret = true;
			}

		}
	}
	return ret;
}

void closeBorder() {
	for (int i = 0; i < N * N;++i) {
		nations[i].root = nations[i].num;
		nations[i].children.clear();
	}
}
void movePeople() {
	printMap();
	for (int i = 0; i < N*N; ++i) {
		//������ ��Ʈ�� ���� �α��̵�
		if (nations[i].num == nations[i].root) {
			int sum = nations[i].pop;

			for (auto c : nations[i].children) {
				sum += nations[c].pop;
			}
			int npop = sum / (nations[i].children.size() + 1);

			for (auto c : nations[i].children) {
				nations[c].pop = npop;
			}
			nations[i].pop = npop;
		}
	}
	printMap();
	closeBorder();
}

int main(void) {
	input();
	int pop;
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &pop);
			nations.push_back(Nation(i * N + j, pop, i, j));
		}
	}
	int res = 0;
	while (openBorder()) {
		++res;
		movePeople();
	}
	printf("%d", res);

	return 0;
}