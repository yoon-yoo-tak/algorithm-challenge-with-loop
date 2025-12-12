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

struct tree {
    ll x, y, c;
};

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
    vector<tree> trees(n);
    vector<ll> x_pos, y_pos;

    for (int i = 0; i < n; i++) {
        cin >> trees[i].x >> trees[i].y >> trees[i].c;
        x_pos.push_back(trees[i].x);
        y_pos.push_back(trees[i].y);
    }

    sort(all(x_pos));
    sort(all(y_pos));

    int answer = n;

    for (int i = 0; i < n; i++) {
        ll mn_x = x_pos[i];
        for (int j = i; j < n; j++) {
            ll mx_x = x_pos[j];
            ll width = mx_x - mn_x;

            for (int yi = 0; yi < n; yi++) {
                ll mn_y = y_pos[yi];
                for (int yj = yi; yj < n; yj++) {
                    ll mx_y = y_pos[yj];
                    ll height = mx_y - mn_y;

                    ll per = 2LL * (width + height);

                    int out_cnt = 0;
                    ll out_total = 0;
                    vector<ll> inside;

                    for (auto& t: trees) {
                        if (mn_x <= t.x && t.x <= mx_x && mn_y <= t.y && t.y <= mx_y) {
                            inside.push_back(t.c);
                        }else {
                            out_cnt++;
                            out_total += t.c;
                        }
                    }

                    if (out_cnt >= answer) continue;

                    ll need = per - out_total;

                    if (need <= 0) {
                        answer = min(answer, out_cnt);
                        continue;
                    }

                    sort(all(inside), greater<ll>());

                    ll s = 0;
                    int cnt = out_cnt;
                    bool flag = false;
                    for (ll c : inside) {
                        s += c;
                        cnt++;
                        if (s >= need) {
                            flag = true;
                            break;
                        }
                        if (cnt >= answer) break;
                    }
                    if (flag) answer = min(answer, cnt);
                }
            }
        }
    }

    cout << answer << endl;

    return 0;
}
