T = int(input())

def gcd(a, b):
  if a < b:
    tmp = b
    b = a
    a = tmp
  
  if b == 0:
    return a
  else:
    return gcd(b, a % b)
  
for _ in range(T):
  A, B = map(int, input().split())
  gcdValue = gcd(A, B)
  print(int(gcdValue * (A/gcdValue) * (B/gcdValue)))

