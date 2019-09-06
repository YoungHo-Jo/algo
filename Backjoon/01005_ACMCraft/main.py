DEBUG = False 
def log(s):
  if DEBUG == True:
    print(s)

T = int(input())
for t in range(0, T):
  N, K = map(lambda x: int(x), input().split())
  timeToConstruct = list(map(lambda x: int(x), input().split()))
  orderToConstruct = {}
  for K in range(0, K):
    lhs, rhs = map(lambda x: int(x), input().split())
    if rhs - 1 in orderToConstruct: # lhs to rhs 
      orderToConstruct[rhs - 1].append(lhs - 1)
    else:
      orderToConstruct[rhs - 1] = [lhs - 1]
  toConstrcut = int(input())

  cache = {} # the maximum required time when n(depth)
  st = [toConstrcut - 1]
  while len(st) != 0:
    front = st[0]
    log('front: {} cache? {}'.format(front, front in cache))
    isPop = False 
    if not front in orderToConstruct: # start 
      log('there is no where to go: {}'.format(front))
      cache[front] = timeToConstruct[front]      
    else:
      maxValue = 0 
      for lhs in orderToConstruct[front]:
        log('lhs: {}'.format(lhs))
        if lhs in cache:
          maxValue = max(maxValue, cache[lhs] + timeToConstruct[front])
        else:
          isPop = True
          st.insert(0, lhs)
          break 
      if isPop == False: 
        cache[front] = maxValue
    if isPop == False: 
      st.pop(0)
    log(st)
    log(cache)

  print(cache[toConstrcut - 1])



