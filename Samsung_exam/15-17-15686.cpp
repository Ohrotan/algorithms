//2020.10.15
//�б�(5) 14:26 ~ 14:31
//Ǯ��(9) 14:31 ~ 14:42
//�ڵ�(33) 14:42 ~ 15:15
//�����(13) 15:15 ~ 15:28
//��(60)

//������ ����� �ʾҰ�, �������� ��Ʈ��ŷ DFS
//ġŲ�� 1���̻� ������ϴ� ���Ƕ����� ������ �־���.
//���� �ݴ� �Ÿ� �������ߴµ�, �ݴ� �κп��� ������ �ϴ� ���°ɷ� �ߴ�.
//���������� �̷��� �ϰ� �ð� ������ ��������

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

#define AB(a,b)(a-b>0?a-b:b-a)
#define MAX(a,b)(a>b?a:b)
#define MIN(a,b)(a<b?a:b)

using namespace std;

int N, M;
int c_r[13]; //���� �ִ� ġŲ�� ��ġ
int c_c[13];
int c_cnt = 0;//���� �ִ� ġŲ�� ��
bool c_open[13] = { false, };

int home_r[100];
int home_c[100];
int home_cnt = 0;//����

int res = 987654321;


void printHC() {
	for (int i = 0; i < c_cnt; ++i) {
		printf("(%d, %d ,%s)", c_r[i], c_c[i], c_open[i] ? "o" : "c");
	}
	printf("\n");
	for (int i = 0; i < home_cnt; ++i) {
		printf("(%d, %d) ", home_r[i], home_c[i]);
	}
	printf("\n");
}
//ġŲ�� �ʱ�ȭ
void init(bool status) {
	for (int i = 0; i < c_cnt; ++i) {
		c_open[i] = status;
	}
}

//���� ���� ����� ġŲ�� �Ÿ�
int chic_dis(int home_num) {
	int dis = 987654321;
	for (int i = 0; i < c_cnt; ++i) {
		if (c_open[i]) {
			int rd = AB(home_r[home_num], c_r[i]);
			int cd = AB(home_c[home_num], c_c[i]);
			dis = MIN(dis, rd + cd);
		}
	}
	return dis;
}
//���� ġŲ �Ÿ�
int city_chic_dis() {
	int dis = 0;
	for (int i = 0; i < home_cnt; ++i) {
		dis += chic_dis(i);
	}
	return dis;
}

//�˻��� ġŲ����ȣ, ��������� ġŲ����
void open(int num, int cnt) {
	if (num == c_cnt || cnt > M) {
		return; //��� ġŲ�� �˻糡
	}
	c_open[num] = true;
	cnt++;
	if (cnt > 0 && cnt <= M) {
		int d = city_chic_dis();
		res = MIN(res, d);
	}
	open(num + 1, cnt);

	c_open[num] = false;
	cnt--;
	if (cnt > 0 && cnt <= M) {
		int d = city_chic_dis();
		res = MIN(res, d);
	}
	open(num + 1, cnt);
}

//�˻��� ġŲ����ȣ, ���� ���� ġŲ����
void close(int num, int cnt) {
	if (num == c_cnt || cnt > c_cnt - cnt) {
		return; //��� ġŲ�� �˻糡
	}

	c_open[num] = false;
	cnt++;
	if (c_cnt - cnt <= M) {
		res = MIN(res, city_chic_dis());
	}
	close(num + 1, cnt);

	c_open[num] = true;
	cnt--;
	if (c_cnt - cnt <= M) {
		res = MIN(res, city_chic_dis());
	}
	close(num + 1, cnt);



}
void sol() {
	init(false);
	//printHC();
	open(0, 0);
	//printHC();
	return;
	if (M <= c_cnt / 2) {

	}
	else {
		init(true);
		close(0, 0);
	}
}

int main(void) {
	input();
	int tmp;
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &tmp);
			if (tmp == 1) {
				home_r[home_cnt] = i;
				home_c[home_cnt++] = j;
			}
			if (tmp == 2) {
				c_r[c_cnt] = i;
				c_c[c_cnt++] = j;
			}
		}

	}
	//printHC();
	sol();
	printf("%d", res);
	return 0;
}