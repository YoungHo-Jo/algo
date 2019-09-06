tree = []
cache = {}
n = int(input())
for i in range(0, n):
  line = list(map(lambda x: int(x), input().split()))
  tree.append(line)

def solve(depth, index):
  if depth == n - 1:
    return tree[depth][index]
  if depth in cache and index in cache[depth]:
    return cache[depth][index]

  if not depth in cache:
    cache[depth] = {}
  cache[depth][index] = max([
    solve(depth + 1, index),
    solve(depth + 1, index + 1)
    ]) + tree[depth][index]
  return cache[depth][index]

print(solve(0, 0))
  

