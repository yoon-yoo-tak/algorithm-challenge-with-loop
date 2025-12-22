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


    int n, m, cnt = 0;
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] == 1) cnt++;
        }
    }

    auto recur = [&](const auto&self, int x, int y) -> void {
        for (int i = x;  i <n ; i++) {
            for (int j = y; j < m; j++) {
                if (board[i][j]) {
                    board[i][j] = 0;
                    cnt--;
                    if (!cnt) return;
                    self(self, i, j);
                    return;
                }
            }
        }
    };

    int answer = 0;
    while (cnt) {
        answer++;
        if (board[0][0]) {
            cnt--;
            board[0][0] = 0;
        }
        if (!cnt) break;
        recur(recur, 0, 0);
    }

    cout << answer << endl;
    return 0;
}
