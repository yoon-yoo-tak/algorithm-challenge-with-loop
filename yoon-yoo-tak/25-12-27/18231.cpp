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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int k;
    cin >> k;
    vector<int> destroyed(k), visited(n + 1, 0);

    for (int i = 0; i < k; i++) {
        cin >> destroyed[i];
        visited[destroyed[i]] = 1;
    }

    vector<int> candid;

    for (int i : destroyed) {
        bool flag = true;
        for (int nxt: graph[i]) {
            if (!visited[nxt]) {
                flag = false;
                break;
            }
        }
        if (flag) candid.push_back(i);
    }

    vector<int> covered(n + 1, 0);
    for (int i : candid) {
        covered[i] = 1;
        for (int nxt: graph[i]) covered[nxt] = 1;
    }

    for (int i : destroyed) {
        if (!covered[i]) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << candid.size() << endl;
    for (int i = 0; i < candid.size(); i++) {
        cout << candid[i] << " ";
    }
    return 0;
}