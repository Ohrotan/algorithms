#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


vector<int> result;
int main(void) {
	int T;
	int num;
	int sc;
	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> num;
		int scores[101] = { 0, };
		for (int j = 0; j < 1000; j++) {
			cin >> sc;
			scores[sc]++;
		}
		int * freq = max_element(scores, scores+101);
	
		while (1) {
			int* sec = max_element(freq+1, scores + 101);
			if (*sec != *freq) {
				break;
			}
			freq = sec;
		}
		result.push_back(freq - scores);
	}

	for (int i = 0; i < T; i++) {
		cout << "#" << i+1 << " " << result.at(i) << endl;
	}
}