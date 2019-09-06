#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false);

  int N;
  cin >> N;
  const int MAX = 1001;
  vector<int> dp(MAX, -1);
  vector<int> nums(N, 0);
  for(int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    nums[i] = tmp;
  }  

  function<int(int)> solve = [&](int idx) {
    D(cout << "idx: " << idx << endl;)
    if(idx == N - 1) {
      return 1;
    }
    if(dp[idx] != -1) return dp[idx];
    int maxValue = -1;
    for(int i = idx + 1; i < N; i++) {
      if(nums[i] > nums[idx]) {
        maxValue = max(maxValue, solve(i) + 1);
      }
    }
    if(maxValue == -1) dp[idx] = 1;
    else dp[idx] = maxValue;
    return dp[idx];
  };

  int ans = -1;
  for(int i = 0; i < N; i++) {
    ans = max(ans, solve(i));
  }
  cout << ans << endl;

  return 0;
}