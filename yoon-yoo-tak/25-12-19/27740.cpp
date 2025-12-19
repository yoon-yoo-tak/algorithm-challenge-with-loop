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
    vector<int> arr(n), one_pos;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i]) one_pos.push_back(i);
    }

    int answer = INF;

    char oper1 = 'L',oper2 = 0;
    int cnt1 = 0, cnt2 = 0;

    auto update = [&](int cost, char a, int cnt_a, char b, int cnt_b)->void {
        if (cost < answer) {
            answer = cost;
            oper1 = a; cnt1 = cnt_a;
            oper2 = b; cnt2 = cnt_b;
        }
    };

    update(one_pos.back() + 1, 'L', one_pos.back() + 1, 0, 0);
    update(n - one_pos.front(), 'R', n - one_pos.front(), 0, 0);

    for (int i = 0; i < one_pos.size() - 1; i++) {
        int x = one_pos[i];
        int y = one_pos[i + 1];

        int l_cnt = x + 1;
        int r_cnt = x + 1 + n - y;
        update(l_cnt + r_cnt, 'L', l_cnt, 'R', r_cnt);

        int r_cnt2 = n -y;
        int l_cnt2 = x + 1 + n - y;
        update(l_cnt2 + r_cnt2, 'R', r_cnt2, 'L', l_cnt2);
    }

    string s;
    s.append(cnt1, oper1);
    if (cnt2 > 0) s.append(cnt2, oper2);
    cout << answer << endl << s << endl;


    return 0;
}
