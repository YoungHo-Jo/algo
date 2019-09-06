X = int(input())

sticks = [64]
sumOfSticks = 64
while sumOfSticks != X:
  minStick = sticks[len(sticks) - 1]
  del sticks[len(sticks) - 1]
  dividedStick = int(minStick / 2)

  if sumOfSticks - dividedStick >= X:
    if dividedStick >= 1:
      sticks.append(dividedStick)
    sumOfSticks -= dividedStick
  else:
    if dividedStick >= 1:
      sticks.append(dividedStick)
      sticks.append(dividedStick)

print(len(sticks))





