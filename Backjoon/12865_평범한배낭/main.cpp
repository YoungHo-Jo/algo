#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N, K;
  cin >> N >> K;
  using pii = pair<int, int>;
  vector<pii> items(N);
  for(int i = 0; i < N; i++) {
    int w, v;
    cin >> w >> v;
    items[i] = pii(w, v);
  }

  const int MAX = 101;
  const int MAX_WEIGHT = 100001;
  vector<vector<int>> dp(MAX, vector<int>(MAX_WEIGHT, -1));
  for(int i = 0; i < N; i++) {
    auto& item = items[i];
    if(i == 0) {
      dp[i][0] = 0;
      if(item.first <= K) dp[i][item.first] = item.second;
      continue;
    }
    for(int w = 0; w <= K; w++) {
      if(dp[i - 1][w] != -1) {
        auto weight = w + item.first;
        if(weight <= K) dp[i][weight] = max(dp[i - 1][w] + item.second, dp[i - 1][weight]);
        dp[i][w] = max(dp[i - 1][w], dp[i][w]);
        if(item.first <= K) dp[i][item.first] = max(dp[i - 1][item.first], item.second);
      }
    }
  }


  int ans = INT32_MIN;
  for(int i = 0; i <= K; i++) {
    ans = max(ans, dp[N - 1][i]);
  }
  cout << ans << endl;



  return 0;
}