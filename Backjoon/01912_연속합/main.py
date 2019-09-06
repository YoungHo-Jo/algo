n = int(input())
numList = list(map(int, input().split()))
MIN = 1e-9
cache = [[MIN for _ in range(2)] for _ in range(n)]

for i in range(n):
  if i == 0:
    cache[i][0] = numList[i]
    cache[i][1] = numList[i]
  else:
    cache[i][0] = max(cache[i - 1][1], cache[i - 1][0])
    cache[i][1] = max(numList[i], cache[i - 1][1] + numList[i])
  
print(max(cache[n - 1]))
