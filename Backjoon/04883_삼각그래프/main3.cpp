#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

using pii = pair<int, int>;
using piii = pair<pii, long long>;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false);

  const vector<vector<pii>> posToVisit = {
    {{1, 0}, {0, 1}, {1, 1}},
    {{1, -1}, {1, 0}, {0, 1}, {1, 1}},
    {{1, -1}, {1, 0}}
  };
  int nTest = 1;
  vector<vector<int>> dp(100000, vector<int>(3, 1e9));
  vector<vector<int>> graph(100000, vector<int>(3, 0));

  while(true) {
    int N;
    cin >> N;
    if(N == 0) return 0;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < 3; j++) {
        int tmp;
        cin >> tmp;
        graph[i][j] = tmp;
      }
    }

    auto checkBoundary = [&](pii& e) {
      auto& x = e.first;
      auto& y = e.second;
      if(x < 0 || x >= N || y < 0 || y >= 3) return false;
      return true;
    };

    function<int(pii&)> solve = [&](pii& p) -> int {
      D(cout << "Current: " << p.first << " " << p.second << " " << endl;)
      auto& x = p.first;
      auto& y = p.second;
      if(x == N - 1) {
        if(y == 0) {
          dp[x][y] = graph[x][y] + graph[x][y + 1];
        } else if(y == 1) {
          dp[x][y] =graph[x][y];
        } else if(y == 2) {
          dp[x][y] = 1e9;
        }
        D(cout << dp[x][y] << endl;)
        return dp[x][y];
      }
      if(dp[x][y] != 1e9) return dp[x][y];
      int minValue = dp[x][y];
      for(auto& posToGo: posToVisit[p.second]) {
        auto nextToGo = pii(p.first + posToGo.first, p.second + posToGo.second);
        D(cout << "Next to go: " << nextToGo.first << " " << nextToGo.second << endl;)
        minValue = min(solve(nextToGo) + graph[x][y], minValue);
      }
      dp[x][y] = minValue;
      D(cout << "min: " << minValue << " at: " << x << " " << y << endl;)
      return minValue;
    };

    pii startPos = pii(0, 1);
    solve(startPos);

    cout << nTest << ". " << dp[0][1] << endl;
    nTest++;
    D(cout << "Before Filling" << endl;)
    fill(dp.begin(), dp.end(), vector<int>(3, 1e9));
    D(cout << "After Filling" << endl;)
  }
  

  return 0;
}