#include<iostream>
#include<map>
#include<string>

using namespace std;

int main(void) {

	map<char, int> m;
	string str;

	cin >> str;

	char key;
	map<char, int>::iterator iter;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'a') {
			str[i] -= ('a' - 'A');
		}

		iter = m.find(str[i]);

		if (iter != m.end()) {
			m[iter->first] += 1;
		}
		else {
			m[str[i]] = 1;
		}
	}

	map<char, int>::iterator max_iter = m.begin();
	iter = m.begin()++;
	for (; iter != m.end(); iter++) {
		if (max_iter->second < iter->second) {
			max_iter = iter;
		}
	}

	for (iter = m.begin(); iter != m.end(); iter++) {
		if (max_iter->second == iter->second && max_iter->first!=iter->first) {
			cout << "?";
			return 0;
		}
	}
	cout << max_iter->first;

	return 0;

}