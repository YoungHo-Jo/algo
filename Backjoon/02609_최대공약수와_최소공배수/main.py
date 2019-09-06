def gcd(a, b):
  if a < b:
    tmp = b
    b = a
    a = tmp
  
  if b == 0:
    return a
  else:
    return gcd(b, a % b)

a, b = map(int, input().split())
gcdValue = gcd(a, b)
print(gcdValue)
print(int(gcdValue * (a/gcdValue) * (b/gcdValue)))