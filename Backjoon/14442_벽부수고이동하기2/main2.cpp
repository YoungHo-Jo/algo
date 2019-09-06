#include <iostream>
#include <queue>
#include <utility>
#include <functional>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> pii2;

#define MAX 1000

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false); 
  int N, M, K;
  cin >> N >> M >> K;


  bool map[MAX][MAX] = {false, };
  for(int i = 0; i < N; i++) {
    string line;
    cin >> line;
    for(int j = 0; j < M; j++) {
      map[i][j] = line[j] == '1' ? true : false;
    }
  }

  queue<pii2> q;
  vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(K, false)));
  // bool visited[MAX][MAX][10] = {false, };
  auto pushToQ = [&](int x, int y, int can, int depth) {
    if(x >= 0 && y >= 0 && x < N && y < M && !visited[x][y][can])  {
      D(cout << "Push: " << x << " " << y << " " << can << " " << depth << endl;)
      q.push(pii2(pii(x, y), pii(can, depth)));
    }
  };
  q.push(pii2(pii(0, 0), pii(K, 1)));
  int ans = INT32_MAX;
  while(!q.empty()) {
    auto cur = q.front();
    q.pop();
    auto& x = cur.first.first;
    auto& y = cur.first.second;
    auto& can = cur.second.first;
    auto& depth = cur.second.second;
    D(cout << x << " " << y << " " << can << " " << depth << endl;)
    if(!visited[x][y][can]) {
      if((map[x][y] && can >= 1)) {
        can--;
      } else if(map[x][y]) continue;
      pushToQ(x - 1, y, can, depth + 1);
      pushToQ(x + 1, y, can, depth + 1);
      pushToQ(x, y + 1, can, depth + 1);
      pushToQ(x, y - 1, can, depth + 1);
      visited[x][y][can] = true;
    }
    if(x == N - 1 && y == M - 1) {
      ans = min(ans, depth);      
    }
  }
  ans = (ans == INT32_MAX) ? -1 : ans;
  cout << ans << endl;

  return 0;
}