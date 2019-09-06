N = int(input())

cache = [[0 for j in range(10)] for i in range(N + 1)]
for digit in range(1, N + 1):
  for number in range(0, 10):
    if digit == 1:
      if number == 0:
        cache[digit][0] = 0
      else:
        cache[digit][number] = 1
    else:
      cache[digit][number] = 0
      if number - 1 >= 0:
        cache[digit][number] += cache[digit - 1][number - 1]
      if number + 1 <= 9:
        cache[digit][number] += cache[digit - 1][number + 1]

sum = 0
for n in cache[N]:
  sum += n

print(sum%int(1e9))