//2020.10.06
//�б�(3) 20:57 ~ 21:00
//Ǯ��(10) 21:00 ~ 21:10
//��Ʈ() 
//�ڵ�(40) 21:20 ~ 22:00
//dfs�� �ѹ��� ���,, �׷��� BFS�� �����غ���!!
//�����() 
//��(53)
#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include<queue>

#if DEBUG
#define log(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;

class Room {
public:
	int a;//A�� ���� ����
	int b;
	int c;
	int n; //���� �� �� �л���
	Room(int nn, int aa = -1, int bb = -1, int cc = -1) :n(nn), a(aa), b(bb), c(cc) {}
};

int n, A, B, C; //A���� ����(A<B<C)

queue<Room> q;
int res = 0;

void dfs(char type, int n) {
	int i = 0;
	switch (type) {
	case 'A':
		if (n % A == 0) {
			res = 1;
			break;
		}
		while (res == 0 && A * i < n) {
			dfs('B', (n % A) + A * i++);
		}
		break;
	case 'B':
		if (n % B == 0) {
			res = 1;
			break;
		}
		while (res == 0 && B * i < n) {
			dfs('C', (n % B) + B * i++);
		}
		break;
	case 'C':
		if (n % C == 0) {
			res = 1;
		}
	}
}

int main(void) {
	input();
	scanf("%d %d %d %d", &A, &B, &C, &n);
	dfs('A', n);
	printf("%d",res);
	return 0;
	q.push(Room(n));
	while (q.size() > 0) {
		Room r = q.front(); q.pop();

		while (1) {
			if (r.b == -1 && n - A > 0) {
				q.push(Room(n - A, r.a + 1));
			}
		}
	}


	return 0;
}