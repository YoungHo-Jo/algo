#include <iostream>
#include <vector>

using namespace std;

// 탑 다운은 불가능해 보임

int main(void) {
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;
  vector<vector<int>> dp(N, vector<int>(M, -1e9)); // -1: not reached
  vector<vector<bool>> visited(N, vector<bool>(M, false)); // -1: not reached
  vector<vector<int>> area(N, vector<int>(M, 0)); 
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      int tmp;
      cin >> tmp;
      area[i][j] = tmp;
    }
  }

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++ ) {
      if(i == 0 && j == 0) {
        dp[0][0] = area[0][0]; 
        continue;
      }
      if(i + 1 < N) {
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + area[i + 1][j]);
      }
      if(j + 1 < M) {
        dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + area[i][j + 1]);
      }
      if(j - 1 >= 0) {
        dp[i][j - 1] = max(dp[i][j - 1], dp[i][j] + area[i][j - 1]);
      }
    }
  }

  cout << dp[N - 1][M - 1] << endl;


  return 0;
}