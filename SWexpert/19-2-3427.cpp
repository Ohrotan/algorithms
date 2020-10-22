//2020.10.05
//읽기(5) 14:45 14:50
//풀이(10) 15:10 15:20 
//차트() 
//코딩(45) 15:20 16:05
//fgets로 쓰자
//정올 사이트에서 scanf 뒤에 널값이 두개나 들어가서 getchar 두번치니까 해결됨,, 이거때문에 시간 엄청 날림
//디버깅(30) 16:05 16:35
//합(90)

#pragma warning(disable:4996)
#include <stdio.h>

#include <vector>
#include <algorithm>
#include<limits.h>
using namespace std;

int n;
char buf[500001];
char balls[500000];

int other = 0;//바꿀 상대
int cnt = 0;
char me = 'R';
char you = 'B';

int res = INT_MAX;

int main(void) {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	getchar();
	fgets(buf, 500001,stdin);

	copy(begin(buf), begin(buf) + n, begin(balls)); //초기화
	other = 0;//바꿀 상대
	cnt = 0;
	me = 'R';
	you = 'B';
	//R을 왼쪽으로 옮기기
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
	other = n - 1;//바꿀 상대
	cnt = 0;
	//R을 오른쪽으로 옮기기
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
	other = 0;//바꿀 상대
	cnt = 0;
	me = 'B';
	you = 'R';
	//B를 왼쪽으로 옮기기
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
	other = n - 1;//바꿀 상대
	cnt = 0;
	//B을 오른쪽으로 옮기기
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