//2020.10.13
//읽기(4) 22:22 ~ 22:26
//풀이(10) 22:26 ~ 22:36
//차트() 
//코딩(20) 22:36 ~ 22:56
//디버깅() 
//합(34)

//오 한번에 맞았다. 이번것도 조건이 까다롭지 않았음
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

int n;
int num[11];
int op[10] = { 0, };
int opNum[5]; // +,-,* /
int tmp, maxres = -1987654321, minres = 1987654321;

void compute() {
	tmp = num[0];
	for (int i = 0; i < n-1; ++i) {
		switch (op[i]) {
		case 1:
			tmp = tmp + num[i+1];
			break;
		case 2:
			tmp = tmp - num[i + 1];
			break;
		case 3:
			tmp = tmp * num[i + 1];
			break;
		case 4:
			tmp = tmp / num[i + 1];
			break;
		}
	}
	maxres = maxres < tmp ? tmp : maxres;
	minres = minres > tmp ? tmp : minres;
}

void printOp() {
	for (int i = 0; i < n - 1; ++i) {
		printf("%d",op[i]);
	}
	printf("\n");
}
void locateOp(int sid,int eid, int remain, int opType) {
	if (remain == 0) {
		if (opType < 4) {
			locateOp(0, n - 1, opNum[opType + 1], opType + 1);
		}
		else {
			//마지막 마무리 어떻게 되는지 제대로 생각
			compute();
			return;
		}
	}
	for (int i = sid; i < eid; ++i) {
		if (op[i] != 0) {
			continue;
		}
		else {
			op[i] = opType;
			locateOp(i + 1, eid, remain - 1,opType);
			op[i] = 0;//백트래킹
		}
	}
}

int main(void) {
	input();
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &num[i]);
	}
	scanf("%d %d %d %d", &opNum[1], &opNum[2], &opNum[3], &opNum[4]);
	locateOp(0, n - 1, opNum[1], 1);
	printf("%d\n%d", maxres, minres);
	return 0;
}