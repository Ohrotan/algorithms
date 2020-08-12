//SW Academy 1486 장훈이의 높은 선반
//조란, 2020.08.10 16:05 ~ 16:25, 22:15 ~ 
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
	queue<int> q;
	for (int i = 0; i < n; ++i) {
		
		int popped = q.front();
		tmp = sum - popped;
		q.pop();
		
		if (tmp > b) {
			minTop(q);
		}
		
	}
}

int main(void) {
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