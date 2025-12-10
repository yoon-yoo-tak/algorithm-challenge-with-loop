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

struct edge {
    int a, b;
    ll cost;
};

struct dsu {
    vector<int> par;
    dsu(int n) : par(n) {
        iota(all(par), 0);
    }

    int find(int x) {
        return par[x] == x ? par[x] : par[x] = find(par[x]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        par[b] = a;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<tuple<ll ,ll ,ll>> arr(n);
    ll total = 0;
    for (auto&[a, b, c]: arr) {
        cin >> a >> b >> c;
        total += c;
    }

    vector<edge> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll w = abs(get<0>(arr[i]) - get<0>(arr[j])) + abs(get<1>(arr[i]) - get<1>(arr[j])) + get<2>(arr[i]) + get<2>(arr[j]);
            edges.push_back({i, j, w});
        }
    }

    sort(all(edges), [](const edge& a, const edge&b) {
        return a.cost < b.cost;
    });



    dsu uf(n);
    ll mst = 0;

    for (auto& e : edges) {
        if (uf.find(e.a) != uf.find(e.b)) {
            mst += e.cost;
            uf.merge(e.a, e.b);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << mst - total + get<2>(arr[i]) << ' ';
    }


    return 0;
}