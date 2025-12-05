#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string.h>
#include <vector>
#include <set>
#include <unordered_set>

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

    ll k;
    cin >> k;
    ll k_square = k * k, abs_k = abs(k);

    unordered_set<ll> st;
    ll answer = 0;
    for (ll i = 1; i <= abs_k; i++) {
        if (k_square % i == 0) {
            ll x =2 * k - i - k_square / i;
            ll y = 2 * k + i + k_square / i;
            st.insert(x);
            st.insert(y);
            answer += x + y;
        }
    }

    cout << st.size() << " " << answer << endl;

    return 0;
}
