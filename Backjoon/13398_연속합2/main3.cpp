#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

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

  bool dp[100001] = {false, };
  int ans = INT32_MIN;
  
  function<void(int, int, int)> solve = [&](int idx, int len, int sum) {
    ans = max(ans, sum);
    if(idx >= n || len >= n || dp[idx] == ) return;
    solve(idx + 1, len + 1, sum + nums[idx]);    
    if(len == 0) {
      solve(idx + 1, len, sum);
    } else {
      dp[idx] = true;
      solve(idx + 1, len + 1, sum);
    }
  };

  solve(0, 0, false);
  
  cout << ans << endl;

  return 0;
}