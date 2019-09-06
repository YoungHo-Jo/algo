#include <iostream>
#include <queue>
#include <utility>
#include <complex>
#include <unordered_map>

using namespace std;

typedef pair<int, int> pii;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  int f, s, g, u, d;
  cin >> f >> s >> g >> u >> d;

  queue<pii> q;
  vector<int> visited(f + 1, INT32_MAX);
  auto pushToQ = [&](const int depth, int value) {
    if(value + u <= f && u != 0 && visited[value + u] > depth) {
      q.push(pii(depth, value + u));
      visited[value + u] = depth;
    }
    if(value - d >= 1 && d != 0 && visited[value - d] > depth) {
      q.push(pii(depth, value - d));
      visited[value - d] = depth;
    }
  };

  q.push(pii(0, s));
  visited[s] = 0;
  int ans = INT32_MAX;
  while(q.empty() == false) {
    auto top = q.front();
    q.pop();
    auto& depth = top.first;
    auto& value = top.second;
    D(cout << "Cur: " << depth << " " << value << endl;)
    if(value == g) {
      ans = min(ans, top.first);
    } else {
      pushToQ(depth +  1, value);
    }
  }

  if(ans == INT32_MAX) cout << "use the stairs" << endl;
  else cout << ans << endl;

  return 0;
}