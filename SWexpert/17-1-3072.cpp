//2020.10.06
//�ڵ�() 20:00 ~ 20:43
//�Է°��� �������� ��Ȯ�� �ľ�����
//�Է��� ����� �ƴ��� �켱 Ȯ��!
//�̷� ������ �� �� ���� Ǯ�����
//��(43)

#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>

#if DEBUG
#define log(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

int n;



void init() {
	for (int i = 0; i < 201; ++i) {
		//a[i] = 0; b[i] = 0;
	}
}
int main(void) {
	input();
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		char winner='D';
		char abuf[205];
		char bbuf[205];
		int a[5] = { 0, };
		int b[5] = { 0, };
		int cnt;
		scanf("%d",&cnt);
		log("cnt", cnt);
		fgets(abuf, 205, stdin);
		for (int j = 0; j < cnt*2+1; ++j) {
			switch (abuf[j]) {
			case '4':
				a[4]++;
				break;
			case '3':
				a[3]++;
				break;
			case '2':
				a[2]++;
				break;
			case '1':
				a[1]++;
				break;
			default:
				break;
			}
		}
		scanf("%d", &cnt);
		fgets(bbuf, 205, stdin);
		for (int j = 0; j < cnt*2+1; ++j) {
			switch (bbuf[j]) {
			case '4':
				b[4]++;
				break;
			case '3':
				b[3]++;
				break;
			case '2':
				b[2]++;
				break;
			case '1':
				b[1]++;
				break;
			default:
				break;
			}
		}

		for (int j = 4; j > 0; --j) {
			if (a[j] > b[j]) {
				winner = 'A';
				break;
			}
			else if (a[j] < b[j]) {
				winner = 'B';
				break;
			}
		}
		printf("%c\n", winner);

	}
	return 0;
}