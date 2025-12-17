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

    int n, m;
    cin >> n >> m;

    if (m == 0) {
        for (int i = 0; i < n; i++) {
            cout << 0 << ' ';
        }
        return 0;
    }

    int t = min(n >> 1, m);
    int b = m / t;
    int r = m % t;

    vector<ll> psum;

    for (ll i = 0; i <= t - 1; i++) psum.push_back(i);
    for (ll i = 1; i <= b; i++) psum.push_back(i*t);
    if (r) psum.push_back(m);

    vector<ll> arr;

    for (int i = 1; i < psum.size(); i++) arr.push_back(psum[i] - psum[i - 1]);

    while (arr.size() < n) arr.push_back(0);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    return 0;
}
