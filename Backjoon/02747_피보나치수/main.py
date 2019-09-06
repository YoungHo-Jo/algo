n = int(input())

cache = {} 
def solve(n):
  if n == 1 or n == 2:
    return 1
  if n in cache:
    return cache[n]

  cache[n] = solve(n - 1) + solve(n - 2)
  return cache[n]

print(solve(n)%1e6)
