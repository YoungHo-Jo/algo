#include <iostream>
#include <queue>
#include <utility>
#include <complex>

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
  auto comp = [&](const pii& lhs, const pii& rhs) {
    return abs(lhs.second - g) > abs(rhs.second - g);
  };

  priority_queue<pii, vector<pii>, decltype(comp)> pq(comp);
  auto pushToQ = [&](const int depth, bool isUp, int value) {
    if(isUp && value + u <= f && u != 0) {
      pq.push(pii(depth, value + u));
    } else if(!isUp && value - d >= 1 && d != 0) {
      pq.push(pii(depth, value - d));
    }
  };

  pq.push(pii(0, s));
  pushToQ(1, true, s);
  pushToQ(1, false, s);
  int minValue = INT32_MAX;
  while(pq.empty() == false) {
    auto top = pq.top();
    D(cout << "Cur: " << top.first << " " << top.second << endl;)
    pq.pop();
    if(top.second == g) {
      minValue = min(minValue, top.first);
      break;
    } else if(top.first < minValue) {
      pushToQ(top.first + 1, true, top.second);
      pushToQ(top.first + 1, false, top.second);
    }
  }

  if(minValue == INT32_MAX) cout << "use the stairs" << endl;
  else cout << minValue << endl;

  return 0;
}