N, M = map(int, input().split())
posToFind = list(map(int, input().split()))

queue = [i for i in range(1, N + 1)]

def rightShift(q):
  last = q[len(q) - 1]
  q.pop()
  q.insert(0, last)
  return q

def leftShift(q):
  first = q[0]
  q.pop(0)
  q.append(first)
  return q

ans = 0
while len(posToFind) != 0:
  rightShiftQueue = queue[:]
  leftShiftQueue = queue[:]

  rightShiftCount = 0
  while rightShiftQueue[0] != posToFind[0]: 
    rightShiftQueue = rightShift(rightShiftQueue)
    rightShiftCount += 1

  leftShiftCount = 0
  while leftShiftQueue[0] != posToFind[0]:
    leftShiftQueue = leftShift(leftShiftQueue)
    leftShiftCount += 1

  if rightShiftCount < leftShiftCount:
    leftShiftQueue.pop(0)
    queue = leftShiftQueue
  else:
    rightShiftQueue.pop(0)
    queue = rightShiftQueue

  posToFind.pop(0)
  ans += min(leftShiftCount, rightShiftCount)


print(ans)

  
  


  