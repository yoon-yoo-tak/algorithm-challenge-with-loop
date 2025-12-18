#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string.h>
#include <vector>
#include <set>
#include <unordered_map>

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
    vector<int> indegree(n + 1, 0);

    for (int i = 1 ; i<= n; i++) {
        int a,b;
        cin >> a >> b;
        indegree[a]++;
        indegree[b]++;
        graph[i].push_back(a);
        graph[i].push_back(b);
    }

    queue<int> q;
    vector<int> visited(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (indegree[i] < 2) {
            q.push(i);
        }
    }

    while (q.size()) {
        int cur = q.front(); q.pop();
        if (visited[cur]) continue;
        visited[cur] = 1;
        for (int i = 0; i < graph[cur].size(); i++) {
            if (--indegree[graph[cur][i]] < 2) {
                q.push(graph[cur][i]);
            };
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 2) cnt++;
    }

    cout << cnt << endl;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 2) {
            cout << i << " ";
        }
    }


    return 0;
}
