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

    int n, m, answer = 0;
    cin >> m >> n;

    vector<vector<int>> board(n, vector<int>(m));
    int total = 0;
    int sx = -1, sy = -1;
    for (int i = 0; i< n; i++) {
        for (int j = 0; j< m; j++) {
            cin >> board[i][j];
            if (board[i][j] == 1) total++;
            if (board[i][j] == 2) sx = i, sy = j;
        }
    }

    auto recur = [&](const auto&self, int x, int y, int cnt) -> void {
        for (int i = 0; i < 4; i++) {
            int nx = x;
            int ny = y;
            while (1) {
                nx += dx[i];
                ny += dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                if (board[nx][ny] == 1) {
                    board[nx][ny] = 0;
                    self(self, nx, ny, cnt + 1);
                    board[nx][ny] = 1;
                    break;
                }
                if (board[nx][ny] == 2) {
                    if (cnt == total) {
                        answer++;
                        return;
                    }
                }
            }
        }
    };

    recur(recur, sx, sy, 0);

    cout << answer << endl;
    return 0;
}
