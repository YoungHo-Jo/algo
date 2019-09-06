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
  vector<vector<long long>> dp(100000, vector<long long>(3, INT64_MAX));
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

    auto getPos = [](piii& e) -> pii& { return e.first; };
    auto getCost = [](piii& e) -> long long& { return e.second; };
    auto checkBoundary = [&](pii& e) {
      auto& x = e.first;
      auto& y = e.second;
      if(x < 0 || x >= N || y < 0 || y >= 3) return false;
      return true;
    };

    function<void(pii&, long long)> solve = [&](pii& p, long long cost) {
      D(cout << "Current: " << p.first << " " << p.second << " " << cost << endl;)
      if(checkBoundary(p) == false) return;
      if(dp[p.first][p.second] < cost) return;
      dp[p.first][p.second] = cost;
      for(auto& posToGo: posToVisit[p.second]) {
        auto nextToGo = pii(p.first + posToGo.first, p.second + posToGo.second);
        D(cout << "Next to go: " << nextToGo.first << " " << nextToGo.second << endl;)
        if(checkBoundary(nextToGo)) solve(nextToGo, cost + graph[nextToGo.first][nextToGo.second]);
      }
    };

    auto startPos = pii(0, 1);
    solve(startPos, graph[0][1]);

    cout << nTest << ". " << dp[N - 1][1] << endl;
    nTest++;
    D(cout << "Before Filling" << endl;)
    fill(dp.begin(), dp.end(), vector<long long>(3, INT64_MAX));
    D(cout << "After Filling" << endl;)
  }
  

  return 0;
}