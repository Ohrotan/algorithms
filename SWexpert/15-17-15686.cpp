//2020.10.15
//읽기(5) 14:26 ~ 14:31
//풀이(9) 14:31 ~ 14:42
//코딩(33) 14:42 ~ 15:15
//디버깅(13) 15:15 ~ 15:28
//합(60)

//조건이 어렵지 않았고, 전형적인 백트래킹 DFS
//치킨집 1개이상 열어야하는 조건때문에 오류가 있었다.
//열고 닫는 거를 나누려했는데, 닫는 부분에서 꼬여서 일단 여는걸로 했다.
//실전에서도 이렇게 하고 시간 남으면 나눠보자

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
int c_r[13]; //원래 있는 치킨집 위치
int c_c[13];
int c_cnt = 0;//원래 있는 치킨집 수
bool c_open[13] = { false, };

int home_r[100];
int home_c[100];
int home_cnt = 0;//집수

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
//치킨집 초기화
void init(bool status) {
	for (int i = 0; i < c_cnt; ++i) {
		c_open[i] = status;
	}
}

//집과 가장 가까운 치킨집 거리
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
//도시 치킨 거리
int city_chic_dis() {
	int dis = 0;
	for (int i = 0; i < home_cnt; ++i) {
		dis += chic_dis(i);
	}
	return dis;
}

//검사할 치킨집번호, 현재오픈한 치킨집수
void open(int num, int cnt) {
	if (num == c_cnt || cnt > M) {
		return; //모든 치킨집 검사끝
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

//검사할 치킨집번호, 현재 닫은 치킨집수
void close(int num, int cnt) {
	if (num == c_cnt || cnt > c_cnt - cnt) {
		return; //모든 치킨집 검사끝
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