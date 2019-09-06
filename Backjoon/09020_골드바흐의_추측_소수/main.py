T = int(input())
N = 10000
cache = [1 for _ in range(N + 1)]
for n in range(N + 1):
  if n == 0 or n == 1:
    cache[n] = 0
  elif cache[n] == 1:
    nToD = n + n
    while nToD <= N:
      cache[nToD] = 0
      nToD += n

for _ in range(T):
  n = int(input())

  ans = [-1, -1]
  for i in range(2, N + 1):
    if i > n - i:
      break
    if cache[i] == 1 and cache[n - i] == 1:
      if ans[0] == -1 or ans[1] - ans[0] > n - i - i:
        ans[0] = i
        ans[1] = n - i
  
  print('{} {}'.format(ans[0], ans[1]))

      
       


  