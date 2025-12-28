#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> arr;
int dp[333][333];
int n;
int goalA, goalB ;

bool ok(int x, int y) {
    return x >= goalA && y >= goalB;
}

int recur(int x, int y) {
    if (ok(x, y)) return 0;
    int &ret = dp[x][y];
    if (ret != -1) return ret;
    ret = 1e9;
    if (x < goalA) ret = min(ret, recur(x + 1, y) + 1);
    if (y < goalB) ret = min(ret, recur(x, y + 1) + 1);

    for (int i = 0; i < n; i++) {
        auto &cur = arr[i];
        if (x >= cur[0] && y >= cur[1]) {
            int nx = min(goalA, x + cur[2]);
            int ny = min(goalB, y + cur[3]);
            if (nx == x && ny == y) continue;
            ret = min(ret, recur(nx, ny) + cur[4]);
        }
    }
    return ret;
}

int solution(int alp, int cop, vector<vector<int>> problems) {
    arr = problems;
    n = (int)problems.size();

    goalA = alp;
    goalB = cop;
    for (auto &v : problems) {
        goalA = max(goalA, v[0]);
        goalB = max(goalB, v[1]);
    }
    alp = min(alp, goalA);
    cop = min(cop, goalB);

    memset(dp, -1, sizeof dp);
    return recur(alp, cop);
}
