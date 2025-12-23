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
    string s;
    cin >> n >> s;

    int cnt = 0;

    string stack;

    auto match = [&](const string& x) ->bool {
        if (x.size() < 5) return false;
        int idx = x.size() - 5;

        if (x[idx] != 's') return false;

        char pattern[5] = {'s', 'k', 'e', 'e', 'p'};
        for (int i = 1; i < 5; i++) {
            char c = x[idx + i];
            if (c != pattern[i] && c != '_') return false;
        }
        return true;
    };

    for (char c: s) {
        stack.push_back(c);

        while (match(stack)) {
            stack.resize(stack.size() - 4);
            stack.back() = '_';
            cnt++;
        }
    }

    cout << cnt << endl;

    return 0;
}
