arr = [10, 9, 7, 3, 4, 1, 2, 4, 6, 4, 6, 7, 8]

def bubbleSort(x):
  length = len(x)
  for i in range(length):
    for j in range(length - i - 1):
      if x[j] > x[j+1]:
        x[j], x[j+1] = x[j+1], x[j]
  return x


print("Before: ")
print(arr)
print("After: ")
print(bubbleSort(arr))

