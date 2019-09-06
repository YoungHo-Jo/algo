import sys

for line in sys.stdin: 
  print(line[:len(line) - 1])
  if line.endswith('\n'): continue
  else: break
  