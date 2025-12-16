#include <string>
#include <vector>

using namespace std;

const int mod = 1000000007;

int solution(int n, int count) {
    int answer = 0;
    
    
    vector<vector<long long>> dp(n + 1, vector<long long> (count + 1, -1));
    auto recur = [&](const auto&self, long long cur, long long cnt) -> long long{
        if (cur == 0) return cnt == 0;
        if (cur < cnt || cnt < 0) return 0;
        long long&ret = dp[cur][cnt];
        if(~ret) return ret;
        ret = 0;
        ret += self(self, cur - 1, cnt - 1);
        ret %= mod;
        ret += self(self, cur - 1, cnt) * (cur - 1) * 2;
        ret %= mod;
        return ret;
    };
    
    return recur(recur, n, count) % mod;
}