//2020.10.14
//�б�(10) 13:57 ~ 14:07
//Ǯ��(17) 14:07 ~ 14:24
//��Ʈ() 
//�ڵ�(47) 14:26 ~ 15:13
//�����(51=16,35) 16:26 ~ 16:42 (ī��X, �����) 16:42 ~ 17:17
//��(125)

//���� ī�ǰ� �ȵż� �˼� ���� ���� ����� �ð� ���� �ɷȴ�. ī�Ǵ�� ����� �̿�����
//��������̴� ���ڸ� �߸� �����߰�
//���� �ű�� ���� ���� ��̿��� ������ ���ؼ� ������ϴ��� �ð��� �ɷȴ�

//����Ʈ �Լ� ���� ¥�� ���� Ȯ���ϴ°Ŷ�, ��̿� Ǫ���Ҷ� ������ �����ϱ�

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif

#include <map>
#include<vector>

using namespace std;

int N, K;
int color[13][13];
int hr[11], hc[11];
int dir[11];

int mr[5] = { 0,0,0,-1,1 };
int mc[5] = { 0,1,-1,0,0 };

map<pair<int, int>, vector<int>> board;

void printHorses() {
	for (auto b : board) {
		printf("(%d %d)",b.first.first,b.first.second);
		for (auto it = b.second.begin(); b.second.end() != it; ++it) {
			printf("%d ", *it);
		}
		printf("\n");
	}
	printf("--------------------------\n");
}

void putHorses(pair<int, int> pos, vector<int> horses, bool reverse) {
	vector<int> *pt;

	if (board.find(pos) == board.end()) {
		board.insert(make_pair(pos, vector<int>{}));
	}
	pt = &board.at(pos);
	int last = horses.size();

	if (reverse) {
		for (int i = last - 1; i >= 0; --i) {
			hr[horses[i]] = pos.first;
			hc[horses[i]] = pos.second;
			pt->push_back(horses[i]);
		}
	}
	else {
		for (int i = 0; i < last; ++i) {
			hr[horses[i]] = pos.first;
			hc[horses[i]] = pos.second;
			pt->push_back(horses[i]);
		}
	}
}
vector<int> getHorses(int me) {
	vector<int> ret;
	vector<int> *horses = &board.at(pair<int, int>(hr[me], hc[me]));

	for (int i = 0; i < horses->size(); ++i) {
		if (horses->at(i) == me) {
			ret.assign(horses->begin()+i, horses->end());
			horses->erase(horses->begin()+i,horses->end());
			//mlog("������ �´�?", horses.front());
			return ret;
		}
	}
	//printf("�̷�������\n");

	return ret;
}
bool inboard(int r, int c) {
	if (r >= 1 && c >= 1 && r <= N && c <= N) {
		return true;
	}
	return false;
}
bool turn() {
	bool ret = true;
	int nr, nc;
	for (int i = 1; i <= K; ++i) {
		//printHorses();
		for (int j = 1; j <= 2; ++j) {
			nr = hr[i] + mr[dir[i]];
			nc = hc[i] + mc[dir[i]];
			int col = color[nr][nc];
			//�Ķ��̰ų� ���̰ų�
			if (col == 2 || !inboard(nr, nc)) {
				if (j == 2) {
					break;
				}
				int d = dir[i];
				if (d % 2 == 0) {
					--d;
				}
				else { ++d; }
				dir[i] = d; //�ݴ����
			}
			//����
			else if (col == 1) {
				auto horses = getHorses(i); //���� �� ���� ����
				//�ݴ�� �ױ�
				putHorses(pair<int, int>(nr, nc), horses, true);
				//���� 4ĭ ������ fals����
				if (board.at(pair<int, int>(nr, nc)).size() >= 4) {
					return false;
				}
				break;
			}
			//���
			else if (col == 0) {
	
				auto horses = getHorses(i); //���� �� ���� ����
				putHorses(pair<int, int>(nr, nc), horses, false);
				//���� 4ĭ ������ fals����
				if (board.at(pair<int, int>(nr, nc)).size() >= 4) {
					return false;
				}
				break;
			}
		}
	}
	return true;
}
int main(void) {
	input();
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &color[i][j]);
		}
	}
	for (int i = 1; i <= K; ++i) {
		scanf("%d %d %d", &hr[i], &hc[i], &dir[i]);
		putHorses(pair<int, int>(hr[i], hc[i]), vector<int>{i}, false);
	}
	//printHorses();
	int res = 1;
	while (turn() && res <= 1000) { ++res; }
	if (res > 1000) {
		res = -1;
	}

	printf("%d",  res);
	return 0;
}