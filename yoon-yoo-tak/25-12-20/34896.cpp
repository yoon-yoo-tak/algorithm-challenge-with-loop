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

    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i =0 ; i< n; i++ )cin >> arr[i];
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    ll b;
    cin >> b;

    vector<pll> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = {arr[i], c[i]};
    }
    sort(all(a));
    vector<ll> pos(n);
    vector<int> cost(n);

    for (int i = 0; i < n; i++) {
        pos[i] = a[i].first;
        cost[i] = a[i].second;
    }

    auto ok = [&](ll x) -> bool {
        ll total = 0;
        int mn = cost[0];
        for (int i = 1; i < n; i++) {
            if (pos[i] - pos[i - 1] > x) {
                total += mn;
                if (total > b) return false;
                mn = cost[i];
            }else mn = min(mn, cost[i]);
        }
        total += mn;
        return total <= b;
    };


    ll l = 1, r = 200000000LL, answer = -1;

    while (l <= r) {
        ll mid = l + r >> 1;
        if (ok(mid)) {
            answer = mid;
            r = mid - 1;
        }else l = mid + 1;
    }

    cout << answer << endl;

    return 0;
}