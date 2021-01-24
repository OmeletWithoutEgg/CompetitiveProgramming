import random

n = 1000
m = 1000
sx, sy = 0, 0
tx, ty = 999, 0

def f(i, j):
    if i % 2 == 0:
        return True
    if i % 4 == 1:
        return j == n-1
    if i % 4 == 3:
        return j == 0


A = [[f(i, j) for j in range(m)] for i in range(n)]

res = []
for i in range(n):
    for j in range(m):
        if A[i][j] and (i != sx or j != sy) and(i != tx or j != ty):
            res.append((i, j, int(random.random() * 10000)))

print(n, m)
print(sx, sy, tx, ty)
print(len(res))
for i, j, w in res:
    print(i, j, w)
