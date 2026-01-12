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
    vector<int> arr(n + 1), psum(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (arr[i] == 1) psum[i] = 1;
    }

    for (int i = 1; i <= n; i++) psum[i] += psum[i - 1];

    if (psum[n] >= (int)ceil((double)n / 2)) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (arr[i] == 1) {
            int left = i;
            int right = n - i + 1;
            if (psum[left] >= (int)ceil((double)left / 2) || psum[n] - psum[i - 1] >= (int)ceil((double)right / 2)) {
                cout << 1 << endl;
                return 0;
            }
        }
    }

    cout << 2 << endl;

    return 0;
}
