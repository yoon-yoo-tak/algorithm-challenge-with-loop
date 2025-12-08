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

    int n, t, w;
    cin >> n >> t >> w;
    vector<pii> arr(n);
    for (auto&[ a, b]: arr) cin >> a >> b;

    int l = 0, r = t ,answer = -1;

    auto ok = [&](int x) -> bool {
        vector<vector<int>> dp(n + 1, vector<int>(t + 1, -1));

        auto recur = [&](const auto& self, int cur, int time) -> int {
            if (cur == n) return 0;
            int&ret = dp[cur][time];
            if (~ret) return ret;
            ret = -0x3f3f3f3f;
            ret = max(ret, self(self, cur + 1, time));

            int cost_time = max(0, arr[cur].first - x);
            if (cost_time <= time) {
                ret = max(ret, self(self, cur + 1, time - cost_time) + arr[cur].second);
            }
            return ret;
        };
        return recur(recur, 0, t - x) >= w;
    };

    while (l <= r) {
        int mid = l +r >> 1;
        if (ok(mid)) {
            answer = mid;
            r = mid - 1;
        }else l = mid + 1;
    }

    cout << answer << endl;

    return 0;
}
