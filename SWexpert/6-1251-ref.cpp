#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int INF = 987654321;

struct Edge {
    ll s, e, c;
    const bool operator< (const Edge& rhs) const {
        return c < rhs.c;
    }
};

int N;
double E;
ll x[1000], y[1000], p[1000];
//bool visit[1000];
vector<Edge> edge;

inline ll dist(ll x1, ll y1, ll x2, ll y2) {
    return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
}

inline ll Find(ll x) {
    return x == p[x] ? x : p[x] = Find(p[x]);
}

inline void Union(ll x, ll y) {
    x = Find(x);
    y = Find(y);
    if (x < y)
        p[y] = x;
    else
        p[x] = y;
}

int main() {
    freopen("input.txt", "r", stdin);

    int tc; scanf("%d", &tc);
    for (int t = 1; t <= tc; ++t) {
        //memset(visit, false, sizeof(visit));
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%lld", &x[i]);
            p[i] = i;
        }
        for (int i = 0; i < N; ++i) {
            scanf("%lld", &y[i]);
        }
        scanf("%lf", &E);

        edge.clear();
        for (int i = 0; i < N - 1; ++i) {
            for (int j = i + 1; j < N; ++j) {
                //if ((i == j) || visit[j])
                    //continue;
                edge.push_back({ i,j,dist(x[i],y[i],x[j],y[j]) });
            }
            //visit[i] = true;
        }

        sort(edge.begin(), edge.end());

        ll ans = 0;
        for (int i = 0; i < (int)edge.size(); ++i) {
            Edge e = edge[i];
            ll start = Find(e.s);
            ll end = Find(e.e);
            if (start != end) {
                Union(start, end);
                ans += e.c;
            }
        }
        printf("#%d %.0f\n", t, ans * E);
    }

    return 0;
}