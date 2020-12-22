#include <iostream>
#include <algorithm>
using namespace std;
int n, b;
int s[22];
int ans = 0x3f3f3f3f;
void sol(int idx, int pidx) {
    if (idx >= n) {
        if (pidx >= b)
            ans = min(ans, pidx);
        return;
    }
    sol(idx + 1, pidx + s[idx]);
    sol(idx + 1, pidx);
}
int main() {
    int tc;
    scanf("%d", &tc);
    for (int test = 1; test <= tc; test++) {
        ans = 0x3f3f3f3f;
        scanf("%d%d", &n, &b);
        for (int i = 0; i < n; i++)
            scanf("%d", &s[i]);
        sol(0, 0);
        printf("#%d %d\n", test, ans - b);
    }
    return 0;
}