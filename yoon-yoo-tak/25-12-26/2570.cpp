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

    vector<vector<char> > board(n + 1, vector<char>(n + 1, 0));
    while (m--) {
        int i, j;
        cin >> i >> j;
        board[i][j] = true;
    }

    vector<vector<int> > row(n + 1, vector<int>(n + 1, 0));
    vector<vector<int> > col(n + 1, vector<int>(n + 1, 0));

    int cnt = 1;
    for (int k = -(n - 1); k <= n - 1; k++) {
        int i, j;
        if (k < 0) i = 1, j = i - k;
        else j = 1, i = j + k;
        while (i <= n && j <= n) {
            if (!board[i][j]) {
                row[i][j] = cnt;
                if (i == n || j == n || (i < n && j < n && board[i + 1][j + 1])) cnt++;
            }
            i++, j++;
        }
    }
    int rCnt = cnt;

    cnt = 1;
    for (int k = 2; k <= n * 2; k++) {
        int i, j;
        if (k <= n) i = 1, j = k - i;
        else j = n, i = k - j;
        while (i <= n && j >= 1) {
            if (!board[i][j]) {
                col[i][j] = cnt;
                if (i == n || j == 1 || (i < n && j > 1 && board[i + 1][j - 1])) cnt++;
            }
            i++, j--;
        }
    }

    vector<vector<int> > graph(5555);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!board[i][j]) graph[row[i][j]].push_back(col[i][j]);
        }
    }

    vector<int> A(5555, -1), B(5555, -1);
    vector<char> visited(5555, 0);

    auto recur = [&](auto &&self, int cur) -> bool {
        visited[cur] = 1;
        for (int nxt: graph[cur]) {
            if (B[nxt] == -1 || (!visited[B[nxt]] && self(self, B[nxt]))) {
                A[cur] = nxt;
                B[nxt] = cur;
                return true;
            }
        }
        return false;
    };

    int answer = 0;
    for (int i = 1; i <= rCnt; i++) {
        fill(all(visited), 0);
        if (recur(recur, i)) answer++;
    }

    cout << answer;


    return 0;
}
