inp = list(map(lambda x: int(x), input().split()))
l = inp[0]
m = inp[1]
r = inp[2]
print((l + m)%r)
print((l%r + m%r)%r)
print((l*m)%r)
print((l%r * m%r)%r)
