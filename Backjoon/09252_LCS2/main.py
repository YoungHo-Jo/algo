str1 = input()
str2 = input()

cache = [[0 for _ in range(len(str2) + 1)] for _ in range(len(str1) + 1)]
for i in range(1, len(str1) + 1):
  for j in range(1, len(str2) + 1):
    if i == 1 or j == 1:
      if str1[i - 1] == str2[j - 1]:
        cache[i][j] = 1
    else:
      if str1[i - 1] == str2[j - 1]:
        cache[i][j] = cache[i - 1][j - 1] + 1
    cache[i][j] = max(cache[i][j], cache[i - 1][j], cache[i][j - 1])


# def find(i, j, ans):
#   if i <= 0 or j <= 0:
#     return ''
#   if i == 1 or j == 1:
#     if cache[i][j] != 0:
#       if i == 1:
#         ans = str1[i - 1] + ans
#       else:
#         ans = str2[j - 1] + ans
#     return ans

#   if cache[i][j] - 1 == cache[i - 1][j - 1] and cache[i][j] != max(cache[i - 1][j], cache[i][j - 1]):
#     ans = str1[i - 1] + ans
#     return find(i - 1, j - 1, ans)
#   elif cache[i - 1][j] < cache[i][j - 1]:
#     return find(i, j - 1, ans)
#   else:
#     return find(i - 1, j, ans)

ans = ''
i = len(str1)
j = len(str2)
while i >= 1 or j >= 1:
  if i == 1 or j == 1:
    if cache[i][j] != 0:
      if i == 1:
        ans = str1[i - 1] + ans
      else:
        ans = str2[j - 1] + ans
    break 
  if cache[i][j] - 1 == cache[i - 1][j - 1] and cache[i][j] != max(cache[i - 1][j], cache[i][j - 1]):
    ans = str1[i - 1] + ans
    i = i - 1
    j = j - 1
  elif cache[i - 1][j] < cache[i][j - 1]:
    j = j - 1
  else:
    i = i - 1


print(cache[len(str1)][len(str2)])
print(ans)