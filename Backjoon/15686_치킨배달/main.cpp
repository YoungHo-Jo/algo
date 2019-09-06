#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

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
  int n, m;
  cin >> n >> m;

  vector<pii> homes;
  vector<pii> stores;

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      int tmp;
      cin >> tmp;
      if(tmp == 1) {
        homes.emplace_back(i, j);
      } else if(tmp == 2) {
        stores.emplace_back(i, j);
      }
    }
  }

  auto getDist = [](pii& lhs, pii& rhs) {
    return abs(lhs.first - rhs.first) + abs(lhs.second - rhs.second);
  };

  vector<bool> mask(stores.size() - m , false);
  for(int i = 0; i < m; i++) {
    mask.push_back(true);
  }

  int minDist = INT32_MAX;
  do {
    int sumDist = 0;
    for(auto& h: homes) {
      int cDist = INT32_MAX;
      for(int i = 0; i < mask.size(); i++) {
        if(mask.at(i) == true) {
          cDist = min(cDist, getDist(h, stores.at(i)));
        }
      }
      sumDist += cDist;
    }

    minDist = min(minDist, sumDist);

  } while(next_permutation(mask.begin(), mask.end()));

  cout << minDist << endl;

  return 0;
}
