#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

string solution(string num, int k) {
    int ansCnt = num.size() - k;
    int cur = 0;
    while (k > 0 && cur < num.size()) {
        //k+1 자리 이내에서 가장 크고 앞인 수 찾기
        string::iterator it;
        if (cur + k + 1 >= num.size()) {
            it = max_element(num.begin() + cur, num.end());
        }
        else {
            it = max_element(num.begin() + cur, num.begin() + cur + k + 1);
        }
        //그 숫자 앞으로 다지워
        k -= distance(num.begin() + cur, it);
        num.erase(num.begin() + cur, it);
        cur++;
    }
    while (num.size() > ansCnt) {
        auto it = min_element(num.begin(), num.end());
        num.erase(it);
    }
    return num;
}
void solution4() {
    string res = solution("987654321", 8);
    cout << res << endl;
}