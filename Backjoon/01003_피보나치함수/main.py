T = int(input())
cache = {}

def fibonacci(n):
  if n == 0:
    return {0: 1, 1: 0}
  if n == 1:
    return {0: 0, 1: 1}
  if n in cache:
    return cache[n]
  cache[n] = {0: fibonacci(n - 1)[0] + fibonacci(n - 2)[0],
    1: fibonacci(n - 1)[1] + fibonacci(n - 2)[1]}
  return cache[n]

for i in range(0, T):
  n = int(input())
  result = fibonacci(n)
  print('{} {}'.format(result[0], result[1]))



