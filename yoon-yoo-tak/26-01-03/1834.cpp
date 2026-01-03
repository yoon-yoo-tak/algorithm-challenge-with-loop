#include <bits/stdc++.h>

static const int INF = 1e9;


using namespace std;

struct Edge {
    int to, cap, cost, rev;
};
struct MCMF {
    int N;
    vector<vector<Edge>> G;
    vector<int> dist, pv, pe;
    vector<bool> inq;

    MCMF(int n): N(n), G(n), dist(n), pv(n), pe(n), inq(n) {}

    void addEdge(int s, int t, int cap, int cost) {
        G[s].push_back({t,cap,cost,(int)G[t].size()});
        G[t].push_back({s,0,-cost,(int)G[s].size()-1});
    }
    pair<int,int> minCostMaxFlow(int S, int T, int maxf) {
        int flow = 0, cost = 0;
        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INF);
            fill(inq.begin(), inq.end(), false);
            dist[S] = 0; inq[S] = true;
            queue<int> q; q.push(S);

            while (!q.empty()) {
                int u = q.front(); q.pop();
                inq[u] = false;
                for (int i = 0; i < (int)G[u].size(); ++i) {
                    Edge &e = G[u][i];
                    if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                        dist[e.to] = dist[u] + e.cost;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        if (!inq[e.to]) {
                            inq[e.to] = true;
                            q.push(e.to);
                        }
                    }
                }
            }
            if (dist[T] == INF) break;
            int addf = maxf - flow;
            int v = T;
            while (v != S) {
                addf = min(addf, G[pv[v]][pe[v]].cap);
                v = pv[v];
            }
            v = T;
            while (v != S) {
                Edge &e = G[pv[v]][pe[v]];
                e.cap -= addf;
                G[v][e.rev].cap += addf;
                v = pv[v];
            }
            flow += addf;
            cost += dist[T] * addf;
        }
        return {flow, cost};
    }
};

int n1, n2;
vector<vector<int>> ch1, ch2;
int dp_memo[105][105];
int f(int u, int v) {
    int &ret = dp_memo[u][v];
    if (ret != -1) return ret;

    auto &C = ch1[u];
    auto &D = ch2[v];
    int m = C.size(), n = D.size();

    if (m == 0 || n == 0) {
        return ret = 1;
    }
    int S = 0;
    int T = m + n + 1;
    MCMF mf(T + 1);
    for (int i = 0; i < m; ++i) {
        mf.addEdge(S, 1 + i, 1, 0);
    }
    for (int j = 0; j < n; ++j) {
        mf.addEdge(1 + m + j, T, 1, 0);
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = f(C[i], D[j]);
            mf.addEdge(1 + i, 1 + m + j, 1, -w);
        }
    }

    int wantFlow = min(m, n);
    auto res = mf.minCostMaxFlow(S, T, wantFlow);
    int minCost = res.second;
    int maxWeight = -minCost;

    return ret = 1 + maxWeight;
}
void buildTree(int n, vector<pair<int,int>> &edges, vector<vector<int>> &ch) {
    vector<vector<int>> g(n+1);
    for (auto &e : edges) {
        g[e.first].push_back(e.second);
        g[e.second].push_back(e.first);
    }
    ch.assign(n+1, {});
    auto dfs = [&](const auto&self, int u, int p)->void {
        for (int v: g[u]) if (v != p) {
            ch[u].push_back(v);
            self(self,v, u);
        }
    };
    dfs(dfs,1, 0);
}



int solution(int n, vector<vector<int>> g1, int m, vector<vector<int>> g2) {
    n1 = n;
    n2 = m;
    vector<pair<int,int>> e1(n1-1);
    for (int i = 0; i < n1 - 1; i++){
        e1[i] = {g1[i][0], g1[i][1]};
    }
    vector<pair<int,int>> e2(n2-1);
    for (int i = 0; i < n2 - 1; i++){
        e2[i] = {g2[i][0], g2[i][1]};
    }
    buildTree(n1, e1, ch1);
    buildTree(n2, e2, ch2);
    memset(dp_memo, -1, sizeof dp_memo);
    return f(1, 1);
}