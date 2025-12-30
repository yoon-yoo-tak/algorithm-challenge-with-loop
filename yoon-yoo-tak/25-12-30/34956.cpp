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
    vector<vector<int>> graph(n + 1);
    vector<int> visited(n + 1, 0);

    int mxNode, mxDist;

    set<pii> st;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a  >> b;
        if (a > b) swap(a, b);
        st.insert({a, b});
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        if (st.find({min(a, b), max(a, b)}) != st.end()) {
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
    }

    int longest = 0;
    int s = -1, e = -1;

    auto recur1 = [&](const auto&self, int cur, int prev)->void {
        visited[cur] = 1;
        for (int nxt: graph[cur]) {
            if (nxt == prev) continue;
            if (!visited[nxt]) self(self, nxt, cur);
        }
    };

    auto recur2 = [&](const auto&self, int cur, int prev, int dist)->void {
        if (dist > mxDist) {
            mxDist = dist;
            mxNode = cur;
        }
        for (int nxt: graph[cur]) {
            if (nxt == prev) continue;
            self(self, nxt, cur, dist + 1);
        }
    };

    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;

        if (graph[i].empty()) {
            visited[i] = 1;
            continue;
        }

        recur1(recur1, i, 0);

        mxDist = -1;
        mxNode = i;
        recur2(recur2, i, 0, 0);
        int a = mxNode;

        mxDist = -1;
        mxNode = a;
        recur2(recur2, a, 0, 0);

        int b = mxNode;
        int d = mxDist;

        if (d > longest) {
            longest = d;
            s = a;
            e = b;
        }
    }

    if (longest < 1) cout << -1 << endl;
    else cout << s << " " << e << endl;

    return 0;
}
