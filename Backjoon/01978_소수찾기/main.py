N = int(input())
inp = list(map(int, input().split()))


ans = 0
for n in inp:
  if n == 1:
    continue
  for i in range(2, n + 1):
    if n%i == 0:
      if i == n:
        ans += 1
      else:
        break 

print(ans)
