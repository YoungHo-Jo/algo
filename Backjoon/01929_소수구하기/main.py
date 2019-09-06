M, N = map(int, input().split())
cache = [1 for _ in range(N + 1)]

for n in range(N + 1):
  if n == 0 or n == 1:
    cache[n] = 0
  elif cache[n] == 1:
    if n >= M:
      print(n)
    multiplier = 2
    numToDelete = n*multiplier
    while numToDelete <= N:
      cache[numToDelete] = 0
      multiplier += 1  
      numToDelete = n*multiplier
