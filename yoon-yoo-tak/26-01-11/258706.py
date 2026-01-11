import sys
sys.setrecursionlimit(202020)

def solution(n, tops):
    answer = 0
    last = n * 2
    dp = [-1] * 202020
    def recur(cur):
        if cur == last + 1:
            return 1
        if cur > last + 1:
            return 0
        if dp[cur] != -1:
            return dp[cur]
        ret = 0
        if cur % 2 == 1 and tops[cur // 2] == 1:
            ret += (recur(cur + 1) * 2 + recur(cur + 2))
            ret %= 10007
        else:
            ret += recur(cur + 1) + recur(cur + 2)    
            ret %= 10007
        dp[cur] = ret
        return ret
    return recur(0)
