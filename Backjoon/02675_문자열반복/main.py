N = int(input())
inp = []
for i in range(0, N):
  line = input().split()
  line[0] = int(line[0])
  inp.append(line)

for line in inp:
  result = ''
  for c in line[1]:
    result += c*line[0]
  print(result)

  