#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

using pii = pair<int, int>;
using piii = pair<pii, long long>;

// #define DEBUG
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
  while(true) {
    int N;
    cin >> N;
    if(N == 0) break;
    vector<vector<int>> graph(N, vector<int>(3, 0));
    vector<vector<long long>> visited(N, vector<long long>(3, INT64_MAX));
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < 3; j++) {
        int tmp;
        cin >> tmp;
        graph[i][j] = tmp;
      }
    }

    queue<piii> q;
    auto getPos = [](piii& e) -> pii& { return e.first; };
    auto getCost = [](piii& e) -> long long& { return e.second; };
    auto pushToQ = [&](piii& e) {
      auto& x = getPos(e).first;
      auto& y = getPos(e).second;
      if(x < 0 || x >= N || y < 0 || y >= 3) return false;
      getCost(e) += graph[x][y];
      D(cout << x << " " << y << " " << getCost(e) <<  " | " << graph[x][y] << endl;)
      if(visited[x][y] < getCost(e)) return false;
      else {
        D(cout << "Add the good node" << endl;)
        q.push(e);
        visited[x][y] = getCost(e);
      }
      return true;
    };

    long long ans = INT64_MAX;
    q.push(piii(pii(0, 1), graph[0][1]));
    while(q.empty() == false) {
      auto& front = q.front();
      D(cout << "Current: " << front.first.first << " " << front.first.second << " " << front.second << endl;)

      if(front.first.first == N - 1 && front.first.second == 1) {
        ans = min(ans, front.second);
      }

      q.pop();
      if(getCost(front) > visited[front.first.first][front.first.second]) {
        D(cout << "This path is not good" << endl;)
        continue;
      }

      for(auto& posOffset: posToVisit[getPos(front).second]) {
        piii newPos = front;
        getPos(newPos).first += posOffset.first;
        getPos(newPos).second += posOffset.second;
        pushToQ(newPos);
      }

    }

    cout << nTest << ". " << ans << endl;
    nTest++;
    graph.clear();
    visited.clear();
  }
  

  return 0;
}