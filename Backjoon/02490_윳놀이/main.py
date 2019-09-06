def solve(inp):
  sum = 0
  for yut in inp:
    if yut == '1':
      sum += 1

  ret = ''    
  if sum == 0:
    ret = 'D'
  elif sum == 1:
    ret = 'C'
  elif sum == 2:
    ret = 'B'
  elif sum == 3:
    ret = 'A'
  else:
    ret = 'E'
  return ret

for _ in range(3):
  line = input().split()
  print(solve(line))

