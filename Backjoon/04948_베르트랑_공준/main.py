MAX = 123456

cache = [1 for _ in range(MAX*2 + 1)]

for n in range(MAX*2 + 1):
  if n == 0 or n == 1:
    cache[n] = 0
  elif cache[n] == 1:
    mul = 2
    nToD = n*mul
    while nToD <= MAX*2:
      cache[nToD] = 0
      mul += 1
      nToD = n*mul

while True:
  inp = int(input())
  if inp == 0:
    break

  ans = 0
  for n in range(inp + 1, 2*inp + 1):
    if cache[n] == 1:
      ans += 1 
  
  print(ans)

