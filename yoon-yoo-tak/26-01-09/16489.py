import sys
from decimal import Decimal, getcontext
getcontext().prec = 80


a, b, c = map(Decimal, sys.stdin.readline().split())
x = Decimal(2)
y = Decimal(4)


s = (a + b + c) / x
area_sq = s * (s - a) * (s - b) * (s - c)
s_sqrt = area_sq.sqrt()
R = (a * b * c) / (y * s_sqrt)
r = s_sqrt / s
expr = R * (R - x * r)
if expr < 0:
    expr = Decimal(0)
d = expr.sqrt()
a2, b2, c2 = a * a, b * b, c * c
cosA = (b2 + c2 - a2) / (x * b * c)
cosB = (a2 + c2 - b2) / (x * a * c)
cosC = (a2 + b2 - c2) / (x * a * b)
k = R * (cosA + cosB + cosC)
for val in (s_sqrt, R, r, d, k):
    print(f"{val:.20f}")
