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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<int> u(m), v(m);
    vector<vector<ll>> w;

    w.resize(1);
    w[0].resize(m);

    vector<vector<pii>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[0][i];
        graph[u[i]].push_back({v[i], i});
        graph[v[i]].push_back({u[i], i});
    }

    int k;
    cin >> k;
    w.resize(k + 1);

    for (int i = 1; i <= k; i++) {
        w[i].resize(m);
        for (int j = 0; j < m; j++) cin >> w[i][j];
    }

    vector<vector<ll>> dist(k + 1, vector<ll>(n + 1, LINF));

    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;

    dist[0][a] = 0;
    pq.push({0, a, 0});

    while (pq.size()) {
        auto [dist_x, x, kk] = pq.top(); pq.pop();

        if (dist_x != dist[kk][x]) continue;
        if (x == b) {
            cout << dist_x << endl;
            return 0;
        }

        if (kk < k && dist_x < dist[kk + 1][x]) {
            dist[kk + 1][x] = dist_x;
            pq.push({dist_x, x, kk + 1});
        }

        for (auto [nxt, idx]: graph[x]) {
            if (dist_x + w[kk][idx] < dist[kk][nxt]) {
                dist[kk][nxt] = dist_x + w[kk][idx];
                pq.push({dist_x + w[kk][idx], nxt, kk});
            }
        }
    }

    ll answer = LINF;
    for (int i = 0; i <= k; i++) answer = min(answer, dist[i][b]);
    cout << answer << endl;
    return 0;
}