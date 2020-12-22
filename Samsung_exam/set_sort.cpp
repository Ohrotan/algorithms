#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define log(s,a){}
#define input(){}
#endif
using namespace std;
class numcnt {
public:
	int num;
	int cnt;
	numcnt(int n, int c) :num(n), cnt(c) {}

};
class compSet {
public:
	bool operator() (numcnt a, numcnt b) const {
		if (a.cnt < b.cnt) {
			return true;
		}if (a.cnt == b.cnt) {
			if (a.num < b.num) {
				return true;
			}
		}
		return false;
	}
};

set<numcnt,compSet> numset; //숫자, 등장횟수
int main() {

	numset.insert(numcnt(1,1));
	numset.insert(numcnt(2,1));
	numset.insert(numcnt(3,1));
	numset.insert(numcnt(4,3));
	numset.insert(numcnt(5,2));

	vector<int> ret;
	ret.push_back(0);//0행, 0열 안쓰기때문
	vector<numcnt> tmp;


	//sort(numset.begin(), numset.end());
	for (auto item : numset) {
		tmp.push_back(numcnt(item.num,item.cnt));
	}
	//sort(tmp.begin(), tmp.end());

	for (auto item : tmp) {
		ret.push_back(item.num);
		ret.push_back(item.cnt);
		// numset.erase(el);
	}

	for (auto item : ret) {
		printf("%3d", item);
		//ret.push_back(item.cnt);
		// numset.erase(el);
	}
	return 0;
}