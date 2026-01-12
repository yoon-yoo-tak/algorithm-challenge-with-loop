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
#define NM 101010
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

int n, m;
vector<int> graph[NM];
int arr[NM], euler[NM << 1], in[NM], out[NM], order = 0;

int depth[NM], parent[18][NM];

int visited[NM], cnt[NM * 10], distinct = 0, answer[NM];
int sqrtN;

struct origin_query {
    int a, b;
};

struct query {
    int l, r;
    int idx;
    int lca;
};

void dfs(int cur, int prev) {
    parent[0][cur] = prev;
    in[cur] = ++order;
    euler[order] = cur;
    for (int nxt : graph[cur]) {
        if (nxt == prev) continue;
        depth[nxt] = depth[cur] + 1;
        dfs(nxt, cur);
    }
    out[cur] = ++order;
    euler[order] = cur;
}

int get_lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int i =0; i < 18; i++) {
        if (diff & (1 << i)) a = parent[i][a];
    }
    if (a == b) return a;
    for (int i = 17; i >= 0; i--) {
        if (parent[i][a] != parent[i][b]) {
            a= parent[i][a];
            b = parent[i][b];
        }
    }
    return parent[0][a];
}

bool cmp(const query&a, const query&b) {
    int x = a.l / sqrtN;
    int y = b.l / sqrtN;
    if (x != y) return x < y;
    if (x &1) return a.r > b.r;
    return a.r < b.r;
}

void mos(int x) {
    int a = euler[x];
    int w = arr[a];
    if (visited[a]) {
        cnt[w]--;
        if (cnt[w] == 0) distinct--;
    }else {
        if (cnt[w] == 0) distinct++;
        cnt[w]++;
    }
    visited[a]^=1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i= 1; i <= n; i++)
        cin >> arr[i];

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    depth[1] = 0;
    dfs(1, 0);

    for (int i =1; i < 18; i++) {
        for (int j = 1; j <= n; j++) {
            parent[i][j] = parent[i - 1][j] > 0 ? parent[i - 1][parent[i - 1][j]] : 0;
        }
    }

    cin >> m;

    vector<origin_query> origin(m);

    for (int i = 0; i < m; i++) cin >> origin[i].a >> origin[i].b;

    vector<query> queries;
    for (int i = 0; i < m; i++) {
        int a = origin[i].a;
        int b = origin[i].b;
        if (in[a] > in[b]) swap(a, b);
        int lca = get_lca(a, b);

        query q;
        q.idx = i;
        if (lca == a) {
            q.l = in[a];
            q.r = in[b];
            q.lca = 0;
        }else {
            q.l = out[a];
            q.r = in[b];
            q.lca = lca;
        }
        queries.push_back(q);
    }

    sqrtN = max(1, (int)sqrt(2 * n));

    sort(all(queries), cmp);

    int curL = 1, curR = 0;

    for (auto& q: queries) {
        while (curL > q.l) mos(--curL);
        while (curR < q.r) mos(++curR);
        while (curL < q.l) mos(curL++);
        while (curR > q.r) mos(curR--);

        int ret = distinct;

        if (q.lca) {
            int x = q.lca;
            int y = arr[x];
            if (cnt[y] == 0)ret++;
        }
        answer[q.idx] = ret;
    }
    for (int i = 0; i < m; i++) cout << answer[i] << endl;
    return 0;
}
