import sys
input = sys.stdin.readline

n = int(input())
ls = [list(map(int, input().split())) for _ in range(n)]
q = int(input())

for _ in range(q):
    oper = list(map(int, input().split()))
    if oper[0] == 1:
        i = oper[1] - 1
        ls[i] = [ls[i][-1]] + ls[i][:-1]
    else:
        ls = [list(row) for row in zip(*ls[::-1])]
for i in ls:
    print(*i)