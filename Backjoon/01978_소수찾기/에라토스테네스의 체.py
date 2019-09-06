N = int(input())
inp = list(map(int, input().split()))
maxNum = max(inp)

cache = [1 for _ in range(maxNum + 1)]
end = maxNum**(float(1)/2)

for i in range(int(end) + 1):
  if i == 0 or i == 1:
    cache[i] = 0
  else:
    if cache[i] == 1:
      multiplier = 2
      numToDelete = i*multiplier
      while numToDelete <= maxNum:
        cache[numToDelete] = 0
        multiplier += 1
        numToDelete = i*multiplier

ans = 0
for num in inp:
  if cache[num] == 1:
    ans += 1

print(ans)
  
