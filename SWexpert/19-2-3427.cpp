//2020.10.05
//�б�(5) 14:45 14:50
//Ǯ��(10) 15:10 15:20 
//��Ʈ() 
//�ڵ�(45) 15:20 16:05
//fgets�� ����
//���� ����Ʈ���� scanf �ڿ� �ΰ��� �ΰ��� ���� getchar �ι�ġ�ϱ� �ذ��,, �̰Ŷ����� �ð� ��û ����
//�����(30) 16:05 16:35
//��(90)

#pragma warning(disable:4996)
#include <stdio.h>

#include <vector>
#include <algorithm>
#include<limits.h>
using namespace std;

int n;
char buf[500001];
char balls[500000];

int other = 0;//�ٲ� ���
int cnt = 0;
char me = 'R';
char you = 'B';

int res = INT_MAX;

int main(void) {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	getchar();
	fgets(buf, 500001,stdin);

	copy(begin(buf), begin(buf) + n, begin(balls)); //�ʱ�ȭ
	other = 0;//�ٲ� ���
	cnt = 0;
	me = 'R';
	you = 'B';
	//R�� �������� �ű��
	for (int i = 0; i < n; ++i) {
		if (balls[i] == me) {
			if (i != other) {
				balls[i] = you;
				balls[other] = me;
				++cnt;
				if (res <= cnt) {
					break;
				}
			}
			++other;
		}
	}
	res = min(res, cnt);

	copy(begin(buf), begin(buf) + n, begin(balls));
	other = n - 1;//�ٲ� ���
	cnt = 0;
	//R�� ���������� �ű��
	for (int i = n - 1; i >= 0; --i) {
		if (balls[i] == me) {
			if (i != other) {
				balls[i] = you;
				balls[other] = me;
				++cnt;
				if (res <= cnt) {
					break;
				}
			}
			--other;
		}
	}
	res = min(res, cnt);

	copy(begin(buf), begin(buf) + n, begin(balls));
	other = 0;//�ٲ� ���
	cnt = 0;
	me = 'B';
	you = 'R';
	//B�� �������� �ű��
	for (int i = 0; i < n; ++i) {
		if (balls[i] == me) {
			if (i != other) {
				balls[i] = you;
				balls[other] = me;
				++cnt;
				if (res <= cnt) {
					break;
				}
			}
			++other;
		}
	}
	res = min(res, cnt);

	copy(begin(buf), begin(buf) + n, begin(balls));
	other = n - 1;//�ٲ� ���
	cnt = 0;
	//B�� ���������� �ű��
	for (int i = n - 1; i >= 0; --i) {
		if (balls[i] == me) {
			if (i != other) {
				balls[i] = you;
				balls[other] = me;
				++cnt;
				if (res <= cnt) {
					break;
				}
			}
			--other;
		}
	}
	res = min(res, cnt);
	printf("%d", res);

	return 0;
}