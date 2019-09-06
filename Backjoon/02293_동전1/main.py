n, k = map(lambda x: int(x), input().split())
values = []
for i in range(n):
  values.append(int(input()))

cache = [[0 for _ in range(k + 1)] for _ in range(2)] # The number of cases at the index of the coin
for coinIdx in range(0, n):
  for value in range(1, k + 1):
    cacheRow = coinIdx%2
    referRow = (cacheRow + 1)%2
    coin = values[coinIdx]
    if value - coin == 0:
      cache[cacheRow][value] = cache[referRow][value] + 1
    elif value - coin > 0:
      cache[cacheRow][value] = cache[cacheRow][value - coin] + cache[referRow][value]
    else:
      cache[cacheRow][value] = cache[referRow][value]

print(cache[(n - 1)%2][k])