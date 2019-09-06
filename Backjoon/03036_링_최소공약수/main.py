N = int(input())

def getGCD(a, b):
  if a < b:
    tmp = b
    b = a
    a = tmp

  if b == 0:
    return a
  else:
    return getGCD(b, a % b)

rings = list(map(int, input().split()))
first = rings[0]
for i in range(1, len(rings)):
  ring = rings[i]
  gcd = getGCD(first, ring)
  print('{}/{}'.format(int(first/gcd), int(ring/gcd)))

