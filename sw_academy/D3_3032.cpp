#include<iostream>

using namespace std;

int main(void) {
	int a, b, x, y;
	cin >> a;
	cin >> b;
	if (b > a) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	int dividend = a;
	int divisor = b;
	int rest = 1;
	while (rest) {
		rest = dividend % divisor;
		if (rest == 0) {
			break;
		}
	}
	

	return 0;
}