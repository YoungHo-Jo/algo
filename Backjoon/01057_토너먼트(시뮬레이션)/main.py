N, A, B = map(int, input().split())

nRound = 1
while True:
  roundList = [0]
  startNumber = 1
  for _ in range(int(N/(2**nRound))):
    for __ in range(2**nRound):
      roundList.append(startNumber)
    startNumber += 1
  for _ in range(N%(2**nRound)):
    roundList.append(startNumber)

  print(roundList) 
  if roundList[A] == roundList[B]:
    print(nRound) 
    break
  nRound += 1


  
