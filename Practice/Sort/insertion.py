arr = [1, 6, 7,4,3, 1,2,3, 0, 10, 20, 3,4, 4]
print("Before: ")
print(arr)

def insertionSort(arr):
  length = len(arr)
  for i in range(length):
    indexMin = i
    for j in range(i + 1, length):
      if arr[indexMin] > arr[j]:
        indexMin = j
      arr[i], arr[indexMin] = arr[indexMin], arr[i]
  return arr

print("After: ")
print(insertionSort(arr))
