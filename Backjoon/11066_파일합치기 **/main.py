DEBUG = False 
def log(s):
  if DEBUG == True:
    print(s)

T = int(input())

for _ in range(T):
  K = int(input())
  files = list(map(int, input().split()))
  
  INF = 987654321
  cache = [[-1 for _ in range(K)] for _ in range(K)]
  accum = [0 for _ in range(K)] # 이게 왜 되는건지 정확하게 이해하지 못함....
  for i in range(0, K):
    if i == 0:
      accum[i] = files[i] 
    else:
      accum[i] = accum[i - 1] + files[i]

  def solve(i, j):
    if i >= K or j >= K or i < 0 or j < 0:
      return INF
    if i == j:
      cache[i][j] = 0
      return 0
    if cache[i][j] != -1:
      return cache[i][j]

    cache[i][j] = INF 
    for start in range(i + 1, j + 1):
      tmp = solve(start, j) + solve(i, start - 1) + accum[j]
      if i - 1 >= 0:
        tmp -= accum[i - 1]
      cache[i][j] = min(cache[i][j], tmp)

    return cache[i][j] 

  print(solve(0, K - 1))
