N, X = map(int, input().split())
inp = list(map(int, input().split()))
ans = ''
for n in inp:
  if X > n:
    ans = ans + str(n) + ' '

print(ans)
  