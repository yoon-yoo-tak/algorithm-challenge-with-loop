#include <bits/stdc++.h>

using namespace std;
int solution(int n, vector<vector<int>> edges) {
    int answer = 0;
    vector<vector<int>> v(n + 1);
    for (int i = 0 ; i < edges.size(); i++){
        int a = edges[i][0], b = edges[i][1];
        v[a].push_back(b);
        v[b].push_back(a);
    }

    vector<int> dist(n + 1, -1), dist2(n + 1, -1);

    auto dfs = [&](const auto&self, int cur, int prv, int flag) -> void{
        for (int nxt : v[cur]){
            if (nxt == prv) continue;
            if (flag)
                dist[nxt] = dist[cur] + 1;
            else
                dist2[nxt] = dist2[cur] + 1;
            self(self, nxt, cur, flag);
        }
    };
    dist[1] = 0;
    dfs(dfs, 1, 0, 1);
    int mx = 0, idx = 0;
    for (int i = 1; i <= n; i++){
        if (dist[i] > mx){
            mx = dist[i];
            idx = i;
        }
    }
    dist.clear(); dist.resize(n + 1, -1); // 한 지름에서 모든 정점까지 거리
    dist[idx] = 0;
    dfs(dfs, idx, 0, 1);
    mx = 0;
    int idx2 = -1;
    for (int i = 1; i <= n; i++){
        if (dist[i] > mx){
            mx = dist[i];
            idx2 = i;
        }
    }
    dist2[idx2] = 0;
    dfs(dfs, idx2, 0, 0);
    for (int i = 1; i <= n; i++){
        if (i == idx || i == idx2) continue;
        int a = dist[i];
        int b = dist2[i];
        if (a > b){
            answer = max(answer, a);
        }else{
            answer = max(answer, b);
        }
    }

    return answer;
}