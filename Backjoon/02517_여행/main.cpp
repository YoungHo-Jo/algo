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

vector<vector<int>> path(300, vector<int>(300, 0));
vector<vector<long long>> dp(300, vector<long long>(301, -1e9)); // the maximum value at [idx][count] // -1: not reached
int main(void) {
  ios::sync_with_stdio(false);
  int N, M, K;
  cin >> N >> M >> K;
  for(int i = 0; i < K; i++) {
    int x, y, v;
    cin >> x >> y >> v;
    path[x - 1][y - 1] = max(path[x - 1][y - 1], v);
  } 
  D(
    cout << "path: " << endl;
    for(auto& row: path) {
      for(auto& p: row) {
        cout << p << " ";
      }
      cout << endl;
    }
  )

  // Bottom up
  // function<long long(int, int)> solve = [&](int idx, int cnt) -> long long {
  //   if(cnt <= 0) return -1e9;
  //   if(idx == N - 1) return 0;
  //   if(idx >= N) return  -1e9;
  //   if(dp[idx][cnt] != -1e9) return dp[idx][cnt];
  //   for(int j = idx + 1; j < N; j++) {
  //     if(path[idx][j] != 0) {
  //       dp[idx][cnt] = max(dp[idx][cnt], solve(j, cnt - 1) + path[idx][j]);
  //     }
  //   }
  //   return dp[idx][cnt];
  // };

  // Top down
  for(int i = 0; i < N; i++) {
    for(int j = i + 1; j < N; j++) {
      if(i == 0 && path[i][j] != 0) {
        dp[j][1] = max(dp[j][1], (long long)path[i][j]); // 1 to j with count 1 
        continue;
      }
      for(int cnt = 1; cnt <= M; cnt++) {
        if(dp[i][cnt] != -1 && path[i][j] != 0) { // 1 to i is possible && a path exists i to j
          D(cout << "path at: " << i << " " << j << endl;)
          if(cnt + 1 <= M) {
            D(cout << "cnt: " << cnt << " " << dp[j][cnt + 1] << " " << dp[j][cnt] << " " << path[i][j] << endl;)
            dp[j][cnt + 1] = max(dp[j][cnt + 1], dp[i][cnt] + (long long)path[i][j]);
          }
        }
      }
    }
  }

  long long ans = -1;
  for(auto& possiblePath: dp[N - 1]) {
    D(cout << possiblePath << endl);
    ans = max(ans, possiblePath);
  }
  cout << (ans == -1 ? 0 : ans) << endl;

  // cout << (solve(0, M) < 0 ? 0 : solve(0, M)) << endl;
  D(
    for(int i = 0; i < N; i++) {
      for(int j = 1; j <= M; j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }
  )


    


  return 0;
}