#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;
  vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(3, -1e9))); // -1e9 not reached
  // the maximum value to the destination at position
  vector<vector<bool>> visited(N, vector<bool>(M, false)); // -1: not reached
  vector<vector<int>> area(N, vector<int>(M, 0)); 
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      int tmp;
      cin >> tmp;
      area[i][j] = tmp;
    }
  }

  function<int(int, int, int)> solve = [&](int x, int y, int d) {
    D(cout << "Current: " << x << " " << y << endl;)
    if(x < 0 || y < 0 || x >= N || y >= M) return (int)-1e9;
    if(dp[x][y][d] != -1e9) return dp[x][y][d];
    if(x == N - 1 && y == M - 1) {
      D(cout << "Destination!" << endl;)
      return area[x][y];
    }
    auto go = [&](int toX, int toY, int d) {
      if(toX < 0 || toY < 0 || toX >= N || toY >= M || visited[toX][toY] == true) return (int)-1e9;
      return solve(toX, toY, d) + area[x][y];
    };
    visited[x][y] = true;
    dp[x][y][d] = max({ go(x + 1, y, 0), go(x, y + 1, 1), go(x, y - 1, 2) });
    D(cout << "Value: " << dp[x][y][d] << " at: " << x << " " << y << endl;)
    D(
      cout << "DP === " << endl;
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
          cout << dp[i][j][0] << " ";
          cout << dp[i][j][1] << " ";
          cout << dp[i][j][2] << " | ";
        }
        cout << endl;
      }
    )
    visited[x][y] = false;
    return dp[x][y][d];
  };

  cout << solve(0, 0, 0) << endl;


  return 0;
}