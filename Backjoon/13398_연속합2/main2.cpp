#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  vector<int> nums(n);
  for(int i = 0; i < n; i++) {
    int tmp;
    cin >> tmp;
    nums[i] = tmp;
  }

  using pii = pair<int, int>;
  int dp[2][100001] = {0, }; // [len evne or odd][start idx]
  pii maxAtIdx[100001] = {pii(0, 0), };

  int ans = INT32_MIN;
  int maxPos = 0;

  for(int len = 1; len <= n; len++) {
    for(int i = 0; i < n; i++) {
      if(len == 1) {
        dp[0][i] = nums[i];
        ans = max({ans, dp[0][i]});
        maxAtIdx[i] = {nums[i], len};
        continue;
      } 
      if(i + len - 1 < n) {
        auto& cur = dp[(len - 1)%2][i];
        cur = dp[(len - 2)%2][i] + nums[i + len - 1];
        ans = max({ans, cur});
        if(ans == cur) maxPos = i;
        auto maxValueAtThis = maxAtIdx[i].first < cur ? pii(cur, len) : maxAtIdx[i];
        maxAtIdx[i] = maxValueAtThis;
      }
    }
  } 
  
  int newAns = ans;
  for(int i = 0; i < maxPos; i++) {
    if(maxAtIdx[i].second + i == maxPos - 1) {
      newAns = max(newAns, maxAtIdx[i].first + ans);
    }
  }
  ans = max(newAns, ans);

  cout << ans << endl;

  return 0;
}