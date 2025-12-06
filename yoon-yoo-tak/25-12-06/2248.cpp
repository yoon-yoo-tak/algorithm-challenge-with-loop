#include <bits/stdc++.h>

#define INF 0x3f3f3f3f3f3f3f3f
#define NM 1010100
#define endl '\n'
#define all(x) x.begin(), x.end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0 ,1, 0 ,-1};


int main() {
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    ll n, l, k;
    cin >> n >> l >> k;

    vector<vector<ll>> dp(33, vector<ll>(33, -1));

    auto recur = [&](const auto&self, int a, int b) -> ll {
        if (a >= n || b == l ) return 1LL;
        ll&ret = dp[a][b];
        if (~ret) return ret;
        ret= 0;
        ret += self(self, a + 1, b);
        ret += self(self, a + 1,b + 1);
        return ret;
    };

    for (int i = 1, j = 0; i <= n ; i++) {
        if (recur(recur, i, j) >= k) {
            cout << 0;
        }else {
            cout << 1;
            k -= recur(recur, i, j);
            j++;
        }
    }

    return 0;
}


