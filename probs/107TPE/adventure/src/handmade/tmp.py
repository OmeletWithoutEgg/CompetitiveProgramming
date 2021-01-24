import random
n, m = [int(t) for t in input().split()]
sx, sy, tx, ty = [int(t) for t in input().split()]
A = [input() for i in range(n)]

res = []
for i in range(n):
    for j in range(m):
        if A[i][j] == '.' and (i != sx or j != sy) and(i != tx or j != ty):
            res.append((i, j, int(random.random() * 10000)))

print(n, m)
print(sx, sy, tx, ty)
print(len(res))
for i, j, w in res:
    print(i, j, w)
