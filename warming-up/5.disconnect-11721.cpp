#include<iostream>
#include<string>

using namespace std;

class disconnect {
private:
	string str;
public:
	void setStr() {
		cin >> str;
	}
	void cutStr() {
		for (int i = 0; i < str.length(); i++) {
			printStr(i);
			if ((i + 1) % 10 == 0) {
				printEnter();
			}
		}
	}
	void printStr(int const i) const {
		cout << str[i];
	}
	inline void printEnter() const {
		cout << "\n";
	}
};

int main(void) {
	disconnect* pd = new disconnect;
	pd->setStr();
	pd->cutStr();
	return 0;
}