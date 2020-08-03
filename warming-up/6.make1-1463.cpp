#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

class makeOneByDP {
private: 
	int n;
	int arr[1000001];
public:
	void setNum() {
		cin >> n;
		memset(arr, 0, sizeof(int) * (n + 1));
	}
	void solution() {
		arr[1] = 0;
		for (int i = 2; i <= n; i++) {
			arr[i] = arr[i - 1] + 1;
			if (i % 2 == 0) {
				arr[i] = min(arr[i], arr[i / 2] + 1);
			}
			if (i % 3 == 0) {
				arr[i] = min(arr[i], arr[i / 3] + 1);
			}
		}
	}
	void printMin() {
		cout << arr[n];
	}
};

class makeOneByBFS {
private:
	int n;
	bool visited[1000001];
	queue<pair<int, int>> q;
	int result;
public:
	void setNum() {
		cin >> n;
		result = 0;
		memset(visited, false, sizeof(bool) * (n + 1));
	}

	void solution() {
		int idx = n;
		int cnt = 0;
		q.push(pair<int, int>(idx, cnt));
		while (1) {
			if (idx == 1) {
				result = q.front().second;
				break;
			}

			if (!visited[idx - 1]) {
				q.push(pair<int, int>(idx - 1, cnt + 1));
			}
			if (idx % 2 == 0 && !visited[idx / 2]) {
				q.push(pair<int, int>(idx/2, cnt + 1));
			}
			if (idx % 3 == 0 && !visited[idx / 3]) {
				q.push(pair<int, int>(idx/3, cnt + 1));
			}
			visited[idx] = true;
			q.pop();
			idx = q.front().first;
			cnt = q.front().second;
		}
	}
	void printMin() {
		cout << result;
	}
};

int main(void) {
	//makeOneByDP one;
	makeOneByBFS one;
	one.setNum();
	one.solution();
	one.printMin();
	return 0;
}