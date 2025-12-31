#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string.h>
#include <vector>
#include <set>
#include <unordered_set>

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<string> codes(n);
    unordered_set<string> set;

    for (int i = 0; i < n; i++) {
        cin >> codes[i];
        set.insert(codes[i]);
    }

    unordered_map<string, vector<string>> prefix;

    for (auto &i : codes) {
        for (int j = 1; j <= i.size(); j++) {
            string p = i.substr(0, j);
            string s = i.substr(j);
            prefix[p].push_back(s);
        }
    }

    unordered_map<string, int> dist;

    using P = pair<int, string>;
    priority_queue<P, vector<P>, greater<P>> pq;

    for (auto &w: codes) {
        for (int i = 1; i < w.size(); i++) {
            string p = w.substr(0, i);
            if (set.find(p) != set.end()) {
                string r = w.substr(i);
                int d = i;
                auto iter = dist.find(r);
                if (iter == dist.end() || d < iter->second) {
                    dist[r] = d;
                    pq.push({d, r});
                }
            }
        }
    }

    while (pq.size()) {
        auto [d, r] = pq.top(); pq.pop();

        auto iter = dist.find(r);
        if (iter == dist.end() || d != iter->second) continue;

        if (r.empty()) {
            cout <<d << endl;
            return 0;
        }

        int L = r.size();

        for (int i = 1; i <= L; i++) {
            string w = r.substr(0, i);
            if (set.find(w) != set.end()) {
                string r2 = r.substr(i);
                int d2 = d + i;
                auto iter2 = dist.find(r2);
                if (iter2 == dist.end() || d2 < iter2->second) {
                    dist[r2] = d2;
                    pq.push({d2, r2});
                }
            }
        }

        auto it = prefix.find(r);
        if (it != prefix.end()) {
            for (string &s : it->second) {
                string r2 = s;
                int d2 = d + L;
                auto it2 = dist.find(r2);
                if (it2 == dist.end() || d2 < it2->second) {
                    dist[r2] = d2;
                    pq.push({d2, r2});
                }
            }
        }
    }


    cout << 0 << endl;
    return 0;
}