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
  vector<vector<int>> dp(MAX, vector<int>(2, 0));
  vector<int> nums(N, 0);
  for(int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    nums[i] = tmp;
  }  

  function<int(int)> solve = [&](int idx) {
    D(cout << "idx: " << idx << endl;)
    if(idx >= N) return 0;
    if(idx == N - 1) {
      dp[idx][0] = 1;
      dp[idx][1] = nums[idx];
      D(cout << "Bound" << endl;)
      return dp[idx][0];
    }
    if(dp[idx][0] != -1) {
      D(cout << "HI: " << dp[idx][0] << endl;)
      return dp[idx][0];
    }
    if(nums[idx + 1] > nums[idx]) {
      D(cout << "Bigger than me: " << nums[idx + 1] <<  " " << nums[idx] << endl;)
      dp[idx][0] = solve(idx + 1) + 1;
      dp[idx][1] = nums[];
    } else if(nums[idx + 1] < nums[idx]) {
      D(cout << "Smaller than me " << nums[idx + 1] <<  " " << nums[idx] << endl;)
      int newIdx = idx + 1;
      while(nums[idx] >= nums[newIdx] && newIdx < N) newIdx++;
      D(cout << "new idx: " << newIdx << endl;)
      dp[idx][0] = newIdx == N - 1 ? 1 : solve(newIdx) + 1;
      dp[idx][1] = nums[newIdx];
      solve(idx + 1);
    } else {
      D(cout << "Same with me " << nums[idx + 1] <<  " " << nums[idx] << endl;)
      dp[idx] = solve(idx + 1);
    }
    return dp[idx];
  };

  solve(0);

  int ans = -1;
  for(auto& d: dp) {
    D(cout << d << " ";)
    ans = max(ans, d);
  }
  D(cout << endl;)
  cout << ans << endl;

  return 0;
}