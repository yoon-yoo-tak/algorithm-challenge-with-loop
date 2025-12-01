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

    while (1) {
        string s;
        cin >> s;
        if (s == "0") break;

        int n = s.size();
        vector<vector<int>> dp((1 << n), vector<int>(n, -1));
        int answer = INF;

        auto c_dist = [&](char a, char b) -> int {
            int x = a - 'A';
            int y = b - 'A';
            int dist = abs(x - y);
            return min(dist, 26 - dist);
        };

        auto recur = [&](const auto&self, int bit, int last) -> int { // 현재 상태가 bit이고 마지막에 입력한 글자가 last일때 나머지 글자 입력하는데 필요한 최소 추가 비용
            if (bit == (1 << n) - 1) return 0;

            int&ret = dp[bit][last];
            if (~ret) return ret;
            ret = INF;

            int pos = __builtin_popcount(bit & ((1 << last)- 1)) + 1;

            for (int i = 0; i < n; i++) {
                if (bit & (1 << i)) continue;
                int npos = __builtin_popcount(bit & ((1 << i) - 1));
                ret = min(ret, self(self, bit | (1 << i), i) + 1 + c_dist(s[last], s[i]) + abs(pos - npos));
            }
            return ret;
        };

        for (int i = 0; i < n; i++) {
            answer = min(answer, recur(recur, 1 << i, i) + c_dist('A', s[i]) + 1);
        }

        cout << answer << endl;
    }


    return 0;
}