inp = int(input())
cache = {} # The minimum count when n

def solve(n: int):
  for i in range(1, inp + 1): # 1 ~ inp
    if i == 1:
      cache[i] = 0
    else:
      minValue = i 
      if i%3 == 0 and i//3 in cache:
        minValue = min(minValue, cache[i//3] + 1)
      if i%2 == 0 and i//2 in cache:
        minValue = min(minValue, cache[i//2] + 1)
      cache[i] = min(minValue, cache[i - 1] + 1)

solve(inp)
print(cache[inp])

