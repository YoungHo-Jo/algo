D = int(input())
N = int(input())
players = list(map(lambda x: int(x), input().split(' ')))
players = sorted(players)
players.reverse()
lastTime = float(D*0.9)/players[2] + float(D*0.1)/(players[2] + 5)

ans = float(D*3)
for i in range(3, N):
  p = players[i]
  if p * lastTime < D*0.9:
    ans += p*lastTime
  else:
    ans += D*0.9
    untilD90 = float(D*0.9)/p
    lastD10 = lastTime - untilD90
    ans += lastD10*(p + 5)
        
print(int(ans))


