DEBUG = False
def log(s):
  if DEBUG == True:
    print(s)

M, N = map(int, input().split())
board = []
for i in range(M):
  board.append(list(map(int, input().split())))

cache = [[-1 for _ in range(N)] for _ in range(M)]
def solve(i, j):
  log('start of the function ({}, {}) cache? {}'.format(i, j, cache[i][j]))
  if i == M - 1 and j == N - 1: # Destination
    return 1
  if cache[i][j] != -1: # Memoization
    log('use cache: {} at ({}, {})'.format(cache[i][j], i, j))
    return cache[i][j]  

  d = [(-1, 0), (0, 1), (1, 0), (0, -1)]
  sum = 0
  for (x, y) in d:
    newX = x + i
    newY = y + j
    log('new ({}, {}) at ({}, {})'.format(newX, newY, i, j))
    if newX >= 0 and newX < M and newY >= 0 and newY < N:
      log('Pass the boundary check')
      log('Compare {} v.s. {}'.format(board[newX][newY], board[i][j]))
      if board[newX][newY] < board[i][j]:
        log('Add')
        sum += solve(newX, newY)
  
  log('sum: {} at ({}, {})'.format(sum, i, j))
  cache[i][j] = sum
  return cache[i][j]

print(solve(0, 0))