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
#define MOD 1000000007LL

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int kdx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int kdy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct edge {
    int nxt, w, idx;
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> u(m), v(m), w(m);
    vector<vector<edge>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        graph[u[i]].push_back({v[i], w[i], i});
    }

    vector<ll> answer(m, 0), dist(n + 1), cnt(n + 1), f(n + 1);

    for (int s = 1; s <= n; s++) {
        // dijk
        fill(all(dist), LINF);
        fill(all(cnt), 0);

        priority_queue<pll, vector<pll>, greater<>> pq;
        dist[s] = 0;
        cnt[s] = 1;
        pq.push({0, s});

        while (pq.size()) {
            auto [dist_x, x] = pq.top(); pq.pop();
            if (dist_x != dist[x]) continue;

            for (auto [nxt, w, idx] : graph[x]) {
                ll ndist = dist_x + w;
                if (ndist < dist[nxt]) {
                    dist[nxt] = ndist;
                    cnt[nxt] = cnt[x];
                    pq.push({ndist, nxt});
                }else if (ndist == dist[nxt]) {
                    cnt[nxt] += cnt[x];
                    cnt[nxt] %= MOD;
                }
            }
        }

        vector<pll> order;
        for (int i = 1; i <= n; i++) {
            if (dist[i] < LINF) order.push_back({dist[i], i});
        }

        sort(all(order), [](auto &a, auto &b) {
            return a.first > b.first;
        });

        fill(all(f), 0);

        // dp
        for (auto& [d, u]: order) {
            ll val = 1;
            for (auto [nxt, w, idx] : graph[u]) {
                if (dist[nxt] == dist[u] + w) {
                    val += f[nxt];
                    val %= MOD;
                    answer[idx] += (cnt[u] * f[nxt]) % MOD;
                    answer[idx] %= MOD;
                }
            }
            f[u] = val;
        }
    }

    for (int i = 0; i < m; i++) {
        cout << answer[i] % MOD << endl;
    }


    return 0;
}
