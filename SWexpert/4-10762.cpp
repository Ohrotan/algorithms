//2020.10.03
//읽기(9) 20:15 ~ 20:24 
//풀이(15) 20:25 ~ 20:40
//차트(18) 20:50 ~ 21:08
//코딩(39) 21:09 ~ 21:48
//합(81) 성공인듯? 그러나 시간초과

//2차 풀이(85) 21:50 ~ 23:15
//시간초과로 실패!! 다음에 한번보자.. 
//
//3차 풀이(50) 9:10 ~ 10:00
//합이 0이 되어야 통과한다는 조건 찾아내서 통과!!
//min_element를 min으로 사용해서 틀렸었음
//합(216)

#pragma warning(disable:4996)
#include <stdio.h>

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int tc = 1, TC;
int num;
int input;
vector<int> me;
vector<int> bro;
int res = 0;


void init() {
	me.clear();
	bro.clear();
	res = 0;
}
bool eq() {
	if (me.size() == 0 || bro.size() == 0) {
		return false;
	}
	int sumB = bro.front();
	int sumM = me.front();
	vector<int>::iterator it;

	for (it = bro.begin() + 1; it != bro.end(); ++it) {
		sumB ^= *it;
	}
	for (it = me.begin() + 1; it != me.end(); ++it) {
		sumM ^= *it;
	}
	return sumM == sumB;
}
bool valid() {
	int sumM = me.front();
	vector<int>::iterator it;
	for (it = me.begin() + 1; it != me.end(); ++it) {
		sumM ^= *it;
	}
	int n = sumM;
	while (n) {
		if (n & 1) {
			printf("1");
		}
		else {
			printf("0");
		}
		n >>= 1;
	}
	printf("\t");
	return sumM == 0;
}
void sol() {
	vector<int>::iterator minValue = min_element(me.begin(), me.end());
	for (auto m : me) {
		res += m;
	}
	res -= *minValue;
	return;
}
void dfs2(int i) {

	if (i == me.size()) {
		return;
	}
	vector<int>::iterator minValue = min_element(me.begin(), me.end() - i);
	printf("min: %d ", *minValue);
	bro.push_back(*minValue);
	me.erase(minValue);
	if (eq()) {
		res = accumulate(me.begin(), me.end(), 0);
		return;
	}
	else {
		dfs2(i);
	}
	//원상복귀
	me.push_back(bro.back());
	bro.pop_back();
	dfs2(i + 1);
}
void dfs(int index) {
	int tmp;
	for (int i = index; i < me.size(); ++i) {
		if (bro.size() > me.size()) {
			return;
		}
		//동생 안 주고 다음칸 이동
		dfs(i + 1);
		if (bro.size() != 0 && eq()) {
			tmp = max(accumulate(me.begin(), me.end(), 0), accumulate(bro.begin(), bro.end(), 0));
			res = max(res, tmp);
		}

		//동생 주고 다음칸 이동
		bro.push_back(me[i]);
		me.erase(me.begin() + i);
		if (bro.size() != 0 && eq()) {
			tmp = max(accumulate(me.begin(), me.end(), 0), accumulate(bro.begin(), bro.end(), 0));
			res = max(res, tmp);
		}
		dfs(i + 1);
		me.insert(me.begin() + i, bro.back());
		bro.pop_back();
	}
}
int main(void) {
	freopen("input.txt", "r", stdin);
	scanf("%d", &TC);
	for (; tc <= TC; ++tc) {
		scanf("%d", &num);
		init();
		for (int i = 0; i < num; ++i) {
			scanf("%d", &input);
			me.push_back(input);
		}

		if (valid()) {
			sol();
			printf("#%d %d\n", tc, res);
		}
		else {
			printf("#%d NO\n", tc);
		}
	}
	return 0;
}