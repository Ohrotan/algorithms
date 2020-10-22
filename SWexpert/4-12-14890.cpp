//2020.10.12
//읽기(4) 09:39 ~ 09:43
//풀이(7) 09:43 ~ 09:50
//차트(25) 09:50 ~ 09:55, 10:33 ~ 10:53(가로)
//코딩(17) 10:53 ~ 11:07(가로),11:07 ~ 11:10(세로)
//디버깅(32) 11:10 ~ 11:42
//합(85)

//for문 전에 초기화문제
//디버깅 시간을 줄이면 충분히 풀 수 있다.
//차트에서 불통처리를 어떻게 할지 애매해서 코딩하면서 하자 했던 것이 
//결국 디버깅하는데 시간을 많이 잡아먹었다.
//또 문제는 초기화문제
//변수를 더 많이 쓰자
//코드를 더 단순화 시킬수 있을 것이다.
//코드가 단순화되면 오류가 날 확률이 줄고, 디버깅 시간도 줄인다.


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

int N, L, tmp, before = 0, after = 0, res = 0;
int gap;
bool isBefore = false;
bool disable = false;
int map[100][100] = { 0, };

int main(void) {
	input();
	scanf("%d %d", &N, &L);
	//read
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &tmp);
			map[i][j] = tmp;
		}
	}

	res = N * 2;

	for (int i = 0; i < N; ++i) {
		disable = false;
		isBefore = true;
		before = 1;
		after = 0;
		for (int j = 1; j < N && !disable; ++j) {
			gap = map[i][j] - map[i][j - 1];
			if (isBefore) {
				if (gap == 0) {
					++before;
				}
				else if (gap == 1) {
					if (before >= L) {
						before = 1;
					}
					else {
						//불통
						disable = true;
						/*res--;
						++i;
						j = 1;
						isBefore = true;
						before = 1;
						after = 0;*/
					}
				}
				else if (gap == -1) {
					isBefore = false;
					after = 1;
					if (after == L) {
						before = 0;
						isBefore = true;
					}
				}
				else {
					//불통
					disable = true;
					/*res--;
					++i;
					j = 1;
					isBefore = true;
					before = 1;
					after = 0;*/
				}
			}
			else {
				if (gap == 0) {
					if (++after == L) {
						before = 0;
						isBefore = true;
					}
				}
				else {
					//불통
					disable = true;
					/*res--;
					++i;
					j = 1;
					isBefore = true;
					before = 1;
					after = 0;*/
				}
			}

		}
		if (disable || !isBefore) {
			//printf("i:%d\n", i);
			--res;
		}
		
	}

	disable = false;
	isBefore = false;
	for (int j = 0; j < N; ++j) {
		disable = false;
		isBefore = true;
		before = 1;
		after = 0;
		for (int i = 1; i < N && !disable; ++i) {
			gap = map[i][j] - map[i-1][j];
			if (isBefore) {
				if (gap == 0) {
					++before;
				}
				else if (gap == 1) {
					if (before >= L) {
						before = 1;
					}
					else {
						//불통
						disable = true;
						/*res--;
						++j;
						i = 1;
						isBefore = true;
						before = 1;
						after = 0;*/
					}
				}
				else if (gap == -1) {
					isBefore = false;
					after = 1;
					if (after == L) {
						before = 0;
						isBefore = true;
					}
				}
				else {
					//불통
					disable = true;
					/*res--;
					++j;
					i = 1;
					isBefore = true;
					before = 1;
					after = 0;*/
				}
			}
			else {
				if (gap == 0) {
					if (++after == L) {
						before = 0;
						isBefore = true;
					}
				}
				else {
					//불통
					disable = true;
					/*res--;
					++j;
					i = 1;
					isBefore = true;
					before = 1;
					after = 0;*/
				}
			}

		}
		if (disable || !isBefore) {
			//printf("j:%d\n", j);
			--res;
		}
	}

	printf("%d", res);
	return 0;
}