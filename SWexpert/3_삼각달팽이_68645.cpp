#include <string>
#include <vector>

using namespace std;
vector<vector<int>> res;
int N;
int r, c; //마지막 등록한 위치
int curnum = 1;//마지막 등록한 숫자
int maxnum;
void down() {
    for (int i = 0; i < N; ++i) {
        if (r == N - 1 || res[r + 1][c] != 0) {
            break;
        }
        res[++r][c] = (++curnum);
    }
}
void right() {
    for (int i = 0; i < N; ++i) {
        if (c == N - 1 || res[r][c + 1] != 0) {
            break;
        }
        res[r][++c] = (++curnum);
    }
}
void dia() {
    for (int i = 0; i < N - 1; ++i) {
        if (res[r - 1][c - 1] != 0) {
            break;
        }
        res[--r][--c] = (++curnum);
    }
}

vector<int> solution(int n) {
    N = n;
    //res.resize(N);
    res.assign(N, vector<int>(1));
    for (int i = 0; i < N; ++i) {
        res[i].assign(i+1, 0);
    }
    maxnum = N * (N + 1) / 2;
    r = 0;
    c = 0;
    res[0][0] = 1;
    while (false && curnum < maxnum) {
        down();
        right();
        dia();
    }


    vector<int> ans;
    return ans;
}
void solution3() {
    solution(6);
}