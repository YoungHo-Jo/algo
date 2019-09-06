inp = input().lower()
sumOfChar = {}
for c in inp:
  if c in sumOfChar:
    sumOfChar[c] += 1
  else:
    sumOfChar[c] = 1

sumOfChar = [(k, sumOfChar[k]) for k in sorted(sumOfChar, key=sumOfChar.get, reverse=True)]
if len(sumOfChar) >= 2 and sumOfChar[0][1] == sumOfChar[1][1]:
  print('?')
else:
  print(sumOfChar[0][0].upper())