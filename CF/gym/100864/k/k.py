from random import randint

def shuffle(arr):
    for i in range(len(arr)):
        j = randint(0, i)
        arr[i], arr[j] = arr[j], arr[i]

N, K = [int(t) for t in input().split()]
L = [0] * N
for i in range(N):
    L[i] = int(input()) * 10**15

while True:
    shuffle(L)
    ans = []
    now = {}
    for x in L:
        if check(now, x):
            now[x] = True
        else
            ans.append(now)
            now = {}
    if len(now)
        ans.append(now)
    if len(ans) <= K:
        diff = K - len(ans)
        for b in ans:
            if 


