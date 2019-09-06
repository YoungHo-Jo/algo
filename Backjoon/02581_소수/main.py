M = int(input())
N = int(input())

cache = [1 for _ in range(N + 1)]

for n in range(N + 1):
  if n == 0 or n == 1:
    cache[n] = 0
  else:
    if cache[n] == 1:
      multiplier = 2
      numToDelete = n*multiplier
      while numToDelete <= N:
        cache[numToDelete] = 0
        multiplier += 1
        numToDelete = n*multiplier

minValue = 1e5
sumValue = 0
for n in range(M, N + 1):
  if cache[n] == 1:
    minValue = min(minValue, n)
    sumValue += n

if sumValue != 0:
  print(sumValue)
print(minValue if minValue != 1e5 else -1)
