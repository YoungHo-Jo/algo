#include <iostream>
#include <vector>
#include <algorithm>

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


  int dp[2][100001] = {0, };
  int ans = INT32_MIN;

  for(int len = 1; len <= n; len++) {
    cout << "len: " << len << endl;
    for(int i = 0; i < n; i++) {
      if(len == 1) {
        dp[0][i] = nums[i]; 
        ans = max(ans, dp[0][i]);
        continue;
      } 
      if(i + len - 1 < n) {
        dp[(len - 1)%2][i] = dp[(len - 2)%2][i] + nums[i + len - 1];
        cout << "=> " << dp[(len - 1)%2][i] << endl;
        ans = max(ans, dp[(len - 1)%2][i]);
      }
    }
  } 
  cout << ans << endl;

  return 0;
}