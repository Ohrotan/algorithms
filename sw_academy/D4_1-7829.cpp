//SW Academy 7829 º¸¹°¿Õ ÅÂÇõ
//Á¶¶õ, 2020.08.10 15:23 ~ 15:35

#include<iostream>

using namespace std;
int p;
int T;
int tmp, minV, maxV;

int main(void) {
	cin >> T;
	for (int tc = 1; tc <= T;  ++tc) {
		cin >> p;
		for (int i = 0; i < p; ++i) {
			cin >> tmp;
			//cout << "tmp: " << tmp << ", ";
			if (minV > tmp || minV == 0) {
				minV = tmp;
				//cout << "minV: " << tmp << ", ";
			}
			if (maxV < tmp) {
				maxV = tmp;
				//cout << "maxV: " << tmp << ", ";
			}
		}
		cout << "#" << tc << " " << minV * maxV << endl;
		minV = 0, maxV = 0;
	}

	return 0;
}