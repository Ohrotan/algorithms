#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
using namespace std;

int testNum = 0;
int dayNum = 0;
vector<int> prices;
vector<long long int> profits;


int maxIdx(int i) {
	vector<int>::iterator maxNum;
	maxNum = max_element(prices.begin() + i, prices.end());
	return distance(prices.begin(), maxNum);
}

long long int buyTilSell() {
	int startIdx = 0;
	long long int profit = 0;
	while (1) {
		int endIdx = maxIdx(startIdx);
		if (endIdx == prices.size()) { break; }
		int sum = accumulate(prices.begin() + startIdx, prices.begin() + endIdx, 0);
		//cout << "endIdx: " << endIdx << ", sum: " << sum;
		int cnt = endIdx - startIdx;
		//cout << ", cnt: " << cnt << ", max value: " << prices.at(endIdx);
		profit += ((long long int)cnt * (long long int)prices.at(endIdx)) - (long long int)sum;
		//cout << ", profit: " << profit << endl;
		startIdx = endIdx + 1;
	}
	return profit;
}
int main(void) {

	cin >> testNum;
	for (int i = 0; i < testNum; i++) {
		cin >> dayNum;
		for (int j = 0; j < dayNum; j++) {
			int p;
			cin >> p;
			prices.push_back(p);
		}
		long long int profit = buyTilSell();
		profits.push_back(profit);
		prices.clear();
	}
	for (int i = 0; i < testNum; i++) {
		cout << "#" << i + 1 << " " << profits.at(i) << endl;
	}

	return 0;
}

