#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string.h>
#include <vector>
#include <set>
#include <stack>

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

    int n, q;
    string s;
    cin >> n >> q >> s;

    vector<int> prefix(n + 1, 0), suffix(n + 1, 0);

    stack<char> st;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i];
        while (!st.empty() && st.top() > s[i]) st.pop();
        if (st.empty() || st.top() < s[i]) {
            st.push(s[i]);
            prefix[i + 1]++;
        }
    }

    while (!st.empty()) st.pop();

    reverse(all(s));

    for (int i = 0; i <n; i++) {
        suffix[i + 1] = suffix[i];
        while (!st.empty() && st.top() > s[i]) st.pop();
        if (st.empty() || st.top() < s[i]) {
            st.push(s[i]);
            suffix[i + 1]++;
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << prefix[a - 1] + suffix[n - b] << endl;
    }



    return 0;
}
