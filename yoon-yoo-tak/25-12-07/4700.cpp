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

    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        vector<vector<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            indegree[b]++;
        }

        queue<int> q;
        for (int i = 1 ; i<= n; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        int cnt = 0;
        bool flag = false;
        while (q.size()) {
            if (q.size() > 1) {
                flag = true;
            }

            int cur = q.front();
            q.pop();
            cnt++;
            for (int nxt: graph[cur]) {
                if (--indegree[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }

        if (cnt < n) {
            cout << 0;
        }else if (flag) {
            cout << 2;
        }else {
            cout << 1;
        }
        cout << endl;
    }


    return 0;
}
