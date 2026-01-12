#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string.h>
#include <vector>
#include <set>
#include <stack>

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

    int n, k;
    cin >> k >> n;

    vector<vector<int>> graph(k << 1);

    auto get = [&](int x, int y) -> int {
        if (y == 'B') return 2 * (x - 1) + 1;
        return 2 * (x - 1);
    };

    for (int i = 0; i < n; i++) {
        int l1, l2, l3;
        char c1, c2, c3;
        cin >> l1 >> c1 >> l2 >> c2 >> l3 >> c3;

        int a = get(l1, c1);
        int b = get(l2, c2);
        int c = get(l3, c3);

        graph[a^1].push_back(b);
        graph[b^1].push_back(a);

        graph[a^1].push_back(c);
        graph[c^1].push_back(a);

        graph[b^1].push_back(c);
        graph[c^1].push_back(b);
    }

    vector<int> disc(k << 1, 0), low(k << 1, 0), scc_id(k << 1, -1), in_stack(k << 1, 0);
    stack<int> st;
    int in = 0, scc_cnt = 0;

    auto recur = [&](const auto&self, int cur)->void {
        disc[cur] = low[cur] = ++in;
        st.push(cur);
        in_stack[cur] = 1;

        for (int nxt: graph[cur]) {
            if (!disc[nxt]) {
                self(self, nxt);
                low[cur] = min(low[cur], low[nxt]);
            }else if (in_stack[nxt]) {
                low[cur] = min(low[cur], disc[nxt]);
            }
        }

        if (low[cur] == disc[cur]) {
            while (1) {
                int x = st.top(); st.pop();
                in_stack[x] = 0;
                scc_id[x] = scc_cnt;
                if (x == cur) break;
            }
            scc_cnt++;
        }
    };

    for (int i = 0; i < k*2; i++) if (!disc[i]) recur(recur, i);

    for (int i = 0; i < k; i++) {
        if (scc_id[i << 1] == scc_id[i << 1|1]) {
            cout << -1 << endl;
            return 0;
        }
    }

    vector<int> val(k);

    for (int i = 0; i < k; i++) {
        val[i] = (scc_id[i << 1|1] < scc_id[i << 1]);
    }

    for (int i = 0; i < k; i++) {
        cout << (val[i] ? 'B':'R');
    }

    return 0;
}
