ans = 0
current = 0
for _ in range(4):
  takeoff, takeon = map(int, input().split())
  current -= takeoff
  current += takeon
  ans = max(current, ans)

print(ans)

