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

    int n;
    cin >> n;

    vector<vector<double>> arr(n, vector<double>(n + 1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> arr[i][j];
        }
    }

    const double EPS = 1e-9;


    for (int col = 0; col < n; col++) {
        int sel = col;
        for (int i = col + 1; i < n; i++) {
            if (fabs(arr[i][col]) > fabs(arr[sel][col])) {
                sel= i;
            }
        }

        if (fabs(arr[sel][col]) < EPS) continue;

        if (sel != col) swap(arr[sel], arr[col]);

        double pivot = arr[col][col];

        for (int j = col; j <= n; j++) arr[col][j] /= pivot;

        for (int i = 0; i < n; i++) {
            if (i == col) continue;
            double factor = arr[i][col];
            for (int j = col; j <= n; j++) arr[i][j] -= factor * arr[col][j];
        }
    }


    vector<int> x(n);

    for (int i = 0; i < n; i++) x[i] = (int)llround(arr[i][n]);

    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }

    return 0;
}
