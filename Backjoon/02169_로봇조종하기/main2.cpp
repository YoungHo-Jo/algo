#include <iostream>
#include <vector>
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

  int N, M;
  cin >> N >> M;
  vector<vector<int>> dp(N, vector<int>(M, -1e9)); // -1e9: not reached
  // the maximum value to the destination at position
  vector<vector<vector<int>>> visited(N, vector<vector<int>>(M, vector<int>(2, -1))); // -1: not reached
  vector<vector<int>> area(N, vector<int>(M, 0)); 
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      int tmp;
      cin >> tmp;
      area[i][j] = tmp;
    }
  }

  function<int(int, int)> solve = [&](int x, int y) {
    D(cout << "Current: " << x << " " << y << endl;)
    if(x < 0 || y < 0 || x >= N || y >= M) return (int)-1e9;
    if(dp[x][y] != -1e9) return dp[x][y];
    if(x == N - 1 && y == M - 1) {
      D(cout << "Destination!" << endl;)
      dp[x][y] = area[x][y];
      return area[x][y];
    }
    auto go = [&](int toX, int toY) {
      if(toX < 0 || toY < 0 || toX >= N || toY >= M || visited[toX][toY][0] == x || visited[toX][toY][1] == y) return (int)-1e9;
      visited[toX][toY][0] = x;
      visited[toX][toY][1] = y;
      return solve(toX, toY) + area[x][y];
    };
    dp[x][y] = max({
      go(x + 1, y), go(x, y + 1), go(x, y - 1)
    });
    D(cout << "Value: " << dp[x][y] << " at: " << x << " " << y << " from: " << visited[x][y][0] << " " << visited[x][y][1] << endl;)
    D(
      cout << "DP === " << endl;
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
          cout << dp[i][j] << " ";
        }
        cout << endl;
      }
    )
    return dp[x][y];
  };


  solve(0, 0);

  cout << dp[0][0] << endl;
  


  return 0;
}