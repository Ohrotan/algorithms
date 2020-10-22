//2020.10.14
//�б�(3) 10:10 ~ 10:13
//Ǯ��(7) 10:13 ~ 10:20
//��Ʈ() 
//�ڵ�(6) 10:21 ~ 10:27
//�����() 
//��(16)

//�̰͵� ������ ��ٷ��� �ʰ� �׳� ��üŽ�� DFS�� Ǯ����.

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
using namespace std;

int N;
bool cal[16]; //���������� true
int t[16], p[16]; //�ɸ��� �ϼ�, ����
int res=0;

void accept(int day, int pay) {
	if (day == N + 1) {
		res = res < pay ? pay : res;
		return;
	}
	if (day + t[day] <= N + 1) {
		for (int i = 0; i < t[day]; ++i) {
			cal[day+i] = true;
		}
		accept(day + t[day], pay + p[day]);
	}
	cal[day] = false;
	accept(day + 1, pay);
}

int main(void) {
	input();
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d %d", &t[i], &p[i]);
	}
	accept(1, 0);
	printf("%d", res);
	return 0;
}