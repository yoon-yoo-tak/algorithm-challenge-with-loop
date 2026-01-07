from bisect import bisect_right
pow26 = [1] * 12
for i in range(1, 12):
    pow26[i] = pow26[i-1] * 26

sum_len = [0] * 12
for L in range(1, 12):
    sum_len[L] = sum_len[L-1] + pow26[L]

TOTAL = sum_len[11]

def rank_of(s: str) -> int:
    L = len(s)
    base = sum_len[L-1]
    lex = 0
    for ch in s:
        lex = lex * 26 + (ord(ch) - ord('a'))
    return base + lex + 1

def rank_to_string(r: int) -> str:
    L = 1
    while L <= 11 and r > pow26[L]:
        r -= pow26[L]
        L += 1
    pos = r
    lex_index = pos - 1
    chars = []
    for _ in range(L):
        chars.append(chr(ord('a') + (lex_index % 26)))
        lex_index //= 26
    chars.reverse()
    return ''.join(chars)

def solution(n: int, bans: list) -> str:
    B = len(bans)
    ban_ranks = [rank_of(b) for b in bans]
    ban_ranks.sort()

    lo, hi = 1, TOTAL
    while lo < hi:
        mid = (lo + hi) // 2
        cnt_bans = bisect_right(ban_ranks, mid)
        nonbanned = mid - cnt_bans
        if nonbanned >= n:
            hi = mid
        else:
            lo = mid + 1
    return rank_to_string(lo)