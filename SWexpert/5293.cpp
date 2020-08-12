//SW Academy 5293 홍준이의 숫자놀이
//조란, 2020.08.08 15:36 ~ 18:00
#include<iostream>
#include<iterator>
#include<list>
using namespace std;
int a, b, c, d;
int aa, bb, cc, dd;
list<int> result;
int start;
list<int>::iterator ptr;
void init(int start) {
	aa = a;
	bb = b;
	cc = c;
	dd = d;
	result.clear();
	if (a > 0 && start < 1) {
		result.push_back(0);
		result.push_back(0);
		--aa;
	}
	else if (b > 0 && start < 2) {
		result.push_back(0);
		result.push_back(1);
		--bb;
	}
	else if (c > 0 && start < 3) {
		result.push_back(1);
		result.push_back(0);
		--cc;
	}
	else if (d > 0 && start < 4) {
		result.push_back(1);
		result.push_back(1);
		--dd;
	}
}
void addA(bool isFront) {
	if (isFront) {
		while (aa) {
			result.push_front(0);
			--aa;
		}
	}
	else {
		while (aa) {
			result.push_back(0);
			--aa;
		}
	}
}
void addD(bool isFront) {
	if (isFront) {
		while (dd) {
			result.push_front(1);
			--dd;
		}
	}
	else {
		while (dd) {
			result.push_back(1);
			--dd;
		}
	}
}
void addToFront() {
	if (result.front()) {
		if (bb > 0) {
			addD(true);
			result.push_front(0);
			--bb;
		}
	}
	else {
		if (cc > 0) {
			addA(true);
			result.push_front(1);
			--cc;
		}
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> a >> b >> c >> d;

		if (b == 0 && c == 0) {
			if (a > 0 && b > 0) {
				printf("#%d %s", tc,"impossible");
				continue;
			}
		}
		if (b - c >= 2 || b - c <= -2) {
			printf("#%d %s", tc, "impossible\n");
			continue;
		}
		if ((b == 0 && c > 1) || (c == 0 && b > 1)) {
			printf("#%d %s", tc, "impossible\n");
			continue;
		}
		start = 0;
		init(start);
		int sum = aa + bb + cc + dd;
		while (sum != 0) {
			if (result.back()) {
				while (dd) {
					result.push_back(1);
					--dd;
				}
				if (cc > 0) {
					result.push_back(0);
					--cc;
				}
				else {
					addToFront();
				}
			}
			else {
				while (aa) {
					result.push_back(0);
					--aa;
				}
				if (bb > 0) {
					result.push_back(1);
					--bb;
				}
				else {
					addToFront();
				}
			}
			//이번 while에서 한게 아무것도 없으면
			if (sum == aa + bb + cc + dd) {
				if (start == 3) {
					result.clear();
					break;
				}
				init(++start); //시작값 다시
			}
			else {
				sum = aa + bb + cc + dd;
			}
		}
		printf("#%d ", tc);
		if (result.empty()) {
			printf("%s", "impossible\n");
		}
		else {
			for (ptr = result.begin(); ptr != result.end(); ptr++) {
				printf("%d", *ptr);
			}
			printf("\n");
		}
	}
	return 0;
}