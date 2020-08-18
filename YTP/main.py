L = input().split(',')
g = [[] for i in range(26)]
for i in range(26):
    for c in L[i]:
        g[ord(c) - ord('A')].append(i)

vis = [False] * 26
def dfs(i):
    if vis[i]:
        return
    vis[i] = True
    for j in g[i]:
        dfs(j)

I = input()
for c in I:
    i = ord(c) - ord('A')
    vis = [False] * 26
    dfs(i)
    res = []
    for j in range(26):
        if vis[j]:
            res.append(chr(ord('A')+j))
    print(''.join(res))
