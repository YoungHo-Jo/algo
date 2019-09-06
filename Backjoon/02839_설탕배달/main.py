inp = int(input())
minSum = 1e9
for n5 in range(0, int(inp/5) + 1):
  leftWeight = inp - n5*5
  if leftWeight%3 == 0:
    minSum = min(minSum, n5 + int(leftWeight/3))
  
if minSum == 1e9: 
  minSum = -1
print(minSum)
