T = int(input())

for _ in range(T):
  N = int(input())
  cache = [1, 1, 1, 2, 2, 3, 4, 5, 7, 9]
  start = len(cache)
  
  for i in range(start, N):
    cache.append(cache[i - 1] + cache[i - 5])
  
  print(cache[N - 1])


    

  
  
    
    
  


