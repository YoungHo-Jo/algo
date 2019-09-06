#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

// Totally Not Mine :( it's from Internet 
// Because i was unable to solve it

int main(void) {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  int nums[100000] = {0, };
  for(int i = 0; i < n; i++) {
    int tmp;
    cin >> tmp;
    nums[i] = tmp;
  }

  int dp[2][100001] = {0, };
  int ans = INT32_MIN;

  for(int i = 0; i < n; i++) {
    if(i == 0) {
      dp[0][i] = nums[i];
      dp[1][0] = nums[i];
      dp[1][1] = max(nums[0],  nums[1]);
      continue;
    } 
    dp[0][i] = max(dp[0][i - 1] + nums[i], nums[i]);
    if(i >= 2) dp[1][i] = max(dp[1][i - 1] + nums[i], dp[0][i - 2] + nums[i]);
    ans = max({ans, dp[0][i], dp[1][i]});
  }  

  cout << ans << endl;

  return 0;
}