#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string.h>
#include <vector>
#include <set>

#define INF 0x3f3f3f3f
#define LINF 1e18+5
#define NM 1001010
#define endl '\n'
#define all(x) x.begin(), x.end()

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int kdx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int kdy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};


int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n), y(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    int p, d;
    cin >> p >> d;

    struct edge {
        int u, v, w;
    };

    vector<edge> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
            if (dist >= d) edges.push_back({i, j, dist});
        }
    }

    int N = 1 << (n << 1);

    vector<int> dp(N, INF);

    dp[0] = 0;

    for (auto [u, v, w]: edges) {
        int su = u << 1, sv = v << 1;
        int iu = 1 << su, iv = 1 << sv;

        for (int bit = N - 1; bit >= 0; bit--) {
            int cur = dp[bit];

            if (cur == INF) continue;

            int du = (bit >> su) & 3;
            int dv = (bit >> sv) & 3;
            if (du >= p || dv >= p) continue;

            int nbit = bit + iu + iv;
            dp[nbit] = min(dp[nbit], cur + w);
        }
    }

    int cnt = 0, total = 0;
    for (int bit = 0; bit < N; bit++) {
        if (dp[bit] != INF) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += (bit >> (i << 1)) & 3;
            }

            int tmp = sum >> 1;
            if (tmp > cnt) {
                cnt = tmp;
                total = dp[bit];
            } else if (cnt == tmp) {
                total = min(total, dp[bit]);
            }
        }
    }

    cout << cnt << " " << total << endl;

    return 0;
}
