//2020.10.08
//�б�(7) 20:58 ~ 21:05
//Ǯ��(2) 21:05 ~ 21:07
//��Ʈ() 
//�ڵ�(14) 21:07 ~ 21:21
//����� ���̶� 1 ���̰� ���� �Ҽ��� �����ΰ� ������..
//�����(10) 09:21 ~ 09:31
// double ���� int�� �ٲٴϱ� ���ڰ� �ϳ� ������
// %.lf�� �̿��ؼ� �Ҽ��� ������
//��(33)
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
int resmin, resdir;


int main(void) {
	input();
	double res = 1;
	double first, second;
	int d,dir=0;//����

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lf %lf %d",&first,&second,&d);
		res = res * (second / first);
		dir ^= d;
	}
	printf("%d %.lf", dir, res);
	return 0;
}