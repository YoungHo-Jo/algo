#include <iostream>
#include <map>
#include <vector>
#include <utility>

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
  vector<int> nums(N, 0);
  for(int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    nums[i] = tmp;
  }

  using pii = pair<long, long>;
  map<long, map<long, long>> dp;
  dp[0] = {{nums.front(), 1}};
  for(int i = 1; i < N - 1; i++) {
    for(auto& prev: dp[i - 1]) {
      auto plusOne = prev.first + nums[i];
      auto minusOne = prev.first - nums[i];
      if(plusOne >= 0 && plusOne <= 20) dp[i][plusOne] += prev.second;
      if(minusOne >= 0 && minusOne <= 20) dp[i][minusOne] += prev.second;
    }
  }

  D(
    cout << "DP: " << endl;
    for(auto& item: dp) {
      cout << "Step: " << item.first << endl;
      for(auto& e: item.second) {
        cout << e.first << " " << e.second << endl;
      }
      cout << endl;
    }  
    cout << endl;
  )

  cout << dp[N - 2][nums.back()] << endl;

  return 0;
}

