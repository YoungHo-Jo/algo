n = int(input())
cups = []
for _ in range(n):
  cups.append(int(input()))

cache = [[0 for _ in range(3)] for _ in range(n)] # [the index of the cup][the number of cups that was drunken]
for wineIdx in range(n):
    if wineIdx == 0:
      cache[wineIdx][1] = cups[wineIdx]
      continue
    
    cache[wineIdx][0] = max(cache[wineIdx - 1])
    cache[wineIdx][1] = cache[wineIdx - 1][0] + cups[wineIdx]
    cache[wineIdx][2] = cache[wineIdx - 1][1] + cups[wineIdx]

print(max(cache[n - 1]))
