//2020.10.04
//�б�(3) 21:48 ~ 21:51
//Ǯ��(29) 21:51 ~ 22:20
//��Ʈ() 
//�ڵ�(33) 22:23 ~ 22:56
//�����(34) 22:56 ~ 23:30
//ä������Ʈ�� �̻��ѵ�,, ���� �ٽ� �õ�
//freopen �Ȼ��� �׷���,, ��������� �ð��ʰ���

//dfs�� 2�� �õ�
//�ϴ� ����!! �ð��� �ʹ� �������
// 
//��()

#pragma warning(disable:4996)
#include <stdio.h>
#include <time.h>

#include<queue>
#include<set>
#include<map>
using namespace std;

clock_t st, et;
map<int,int> s;

int N, M, X; //�л���, ����, ����ȣ
int cri = -1; //������ ����� ���� ����
int a, b;//��ǲ

vector<pair<int, int>> stu;//�л��� ���
queue<int> betq;//������ ������ ã�� �� üũ�غ� �л�
queue<int> ambi;//���غ��� ������ ã�� �� üũ�غ� �л�

set<int> better; //������ ���� ��
set<int> range; //���غ��� ���� ��

bool app[100000] = { false, }; //appearance i�� �л��� ���� ����, 
void sol() {
	
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N, &M, &X);
	/*if (N > 100) {
		printf("1 1");
		return;
	}*/
	for (int i = 0; i < M; ++i) {
		scanf("%d %d", &a, &b);

		stu.push_back(pair<int, int>{a, b});
		app[a] = true;
		app[b] = true;

		if (a == X) {
			cri = b; //cri�� �ΰ��ϰ��?
		}
		if (b == X) {
			betq.push(a);
		}
	}

	if (!app[X]) {
		printf("1 %d", N);
		return;
	}

	//������ Ȯ���� ������ ã��
	while (betq.size() > 0) {
		int cr = betq.front(); betq.pop();
		better.insert(cr);
		for (auto p : stu) {
			if (p.second == cr) {
				betq.push(p.first);
			}
		}
	}

	//���غ��� ������ ã��
	if (cri != -1) {
		for (auto p : stu) {
			if (p.second == cri) {
				ambi.push(p.first);
				range.insert(p.first);
			}
		}
		while (ambi.size() > 0) {
			int cr = ambi.front(); ambi.pop();
			if (cr == X || range.find(cr) == range.end())continue;

			for (auto p : stu) {
				if (p.second == cr && range.find(p.first) == range.end()) {

					ambi.push(p.first);
					range.insert(p.first);

				}
				else if (p.first == cr) {
					//p.second�� ������ ������ ������� ������!!
					//������ Ŭ���� �ִ°���
					if (better.find(p.second) == better.end()) {
						range.insert(p.second);
						ambi.push(p.second);
					}

				}

			}
		}
	}
	else {
		int best = better.size() + 1;
		int worst = N;
		printf("%d %d", best, worst);
		
		return;
	}
	range.erase(cri);
	//printf("%d", range.size());

	int cnt = 0;
	for (bool a : app) {
		a ? ++cnt : 1;
	}
	//�������
	int best = better.size() + 1;
	int worst = range.size() + N - cnt;
	printf("%d %d", best, worst);
}
int main(void) {
	st = clock();
	for (int i = 0; i < 1; ++i) {
		sol();
	}
	et = clock();
	printf("time: %lf", (double)(et - st));
	return 0;
}