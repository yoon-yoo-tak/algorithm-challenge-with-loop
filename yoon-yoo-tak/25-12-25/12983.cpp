#include <bits/stdc++.h>
using namespace std;

int solution(vector<string> strs, string t)
{
    int answer = 0;
    int n = t.size();
    vector<int> dp(n + 1, -1);
    auto recur = [&](const auto&self, int cur)->int{
        if(cur == n) return 0;
        int&ret = dp[cur];
        if (~ret) return ret;
        ret = 0x3f3f3f3f;
        for (auto s : strs){
            int m = s.size();
            if (n - cur >= m){
                int same = 0;
                for (int i = 0; i < m; i++){
                    if (t[cur + i] == s[i]) same++;
                }
                if (same == m){
                    ret = min(ret, self(self, cur + m) + 1);
                }
            }
        }
        return ret;
    };

    answer = recur(recur, 0);
    if (answer == 0x3f3f3f3f) answer = -1;
    return answer;
}