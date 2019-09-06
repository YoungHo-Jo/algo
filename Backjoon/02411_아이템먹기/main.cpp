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

  int N, M, A, B;
  cin >> N >> M >> A >> B;
  vector<vector<int>> map(N, vector<int>(M, 0));
  for(int i = 0; i < A + B; i++) {
    int x, y;
    cin >> x >> y;
    if(i < A) map[N - x][y - 1] = 1;
    else map[N - x][y - 1] = 2;
  }


  vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(200, -1))); // -1: not reached
  function<int(int, int, int)> solve = [&](int x, int y, int count) -> int {
    D(cout << "current: " << x << " " << y << " " << endl;)
    if(x < 0 || y < 0 || x >= N || y >= M || map[x][y] == 2 || count < 0) return 0;
    D(cout << "Map: " << map[x][y] << endl;)
    if(x == N - 1 && y == 0 ) return map[x][y] == 1 ? count == 1 ? 1 : 0 : count == 0 ? 1 : 0;
    if(dp[x][y][count] != -1) return dp[x][y][count];
    dp[x][y][count] = map[x][y] == 1 ? solve(x + 1, y, count - 1) + solve(x, y - 1, count - 1) 
      : solve(x + 1, y, count) + solve(x, y - 1, count);
    D(cout << "MAX: " << dp[x][y][count] << " at: " << x << " " << y << " " << count << endl;)
    D(cout << "=======" << endl;)
    return dp[x][y][count];
  };

  int ans = solve(0, M - 1, A);
  cout << (ans < 0 ? 0 : ans) << endl;
  

  return 0;
}