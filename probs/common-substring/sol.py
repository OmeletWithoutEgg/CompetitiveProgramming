n = int(input())
t = []

for i in range(n):
    t.append(input())

first = set(t[0])
print(t)
for i in t:
    first = first&set(i)

if not first:
    print("7122")
else:
    print(first.pop())
