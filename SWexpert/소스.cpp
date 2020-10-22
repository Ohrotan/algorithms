//SW Academy 1486 �������� ���� ����
//����, 2020.08.10 16:05 ~ 16:25, 
// 2020.09.17 15:55 ~
#pragma warning(disable:4996) 
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<numeric>

using namespace std;

int n, b;
vector<int> top;
int sum = 0;
int result = 0;

int minTop(queue<int> q) {
	int tmp;
	
	for (int i = 0; i < n; ++i) {

		int popped = q.front();
		tmp = sum - popped;
		q.pop();

		if (tmp > b) {
			minTop(q);
		}

	}
	return 0;
}

int main2(void) {
	int T;
	scanf("%d", &T);

	int h;
	for (int tc = 1; tc <= T; ++tc) {
		scanf("%d %d", &n, &b);
		sum = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &h);
			top.push_back(h);
			sum += h;
		}
		result = sum;
		int tmp = 0;
		for (int i = 0; i < n; ++i) {
			tmp = sum - top.at(i);
			for (int j = i + 1; j < n; ++j) {
				tmp -= top.at(j);
				if (tmp >= b && result > tmp) {
					result = tmp;
				}
			}
		}
		printf("#%d %d", tc, result - b);


	}
	return 0;
}