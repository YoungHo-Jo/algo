#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <queue>
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

  int N;
  cin >> N;
  vector<vector<char>> board(N, vector<char>(N, '0'));
  using pii = pair<int, int>;
  vector<pii> wood;
  vector<pii> dest;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      char c;
      cin >> c;
      if(c == 'B') wood.emplace_back(i, j);
      else if(c == 'E') dest.emplace_back(i, j);
      else board[i][j] = c;
    }
  } 

  auto moveRight = [&](vector<pii>& wood) {
    for(auto& b: wood) {
      b.second++;
    }
  };
  auto moveLeft = [&](vector<pii>& wood) {
    for(auto& b: wood) {
      b.second--;
    }
  };
  auto moveUp = [&](vector<pii>& wood) {
    for(auto& b: wood) {
      b.first--;
    }
  };
  auto moveDown = [&](vector<pii>& wood) {
    for(auto& b: wood) {
      b.first++;
    }
  };
  auto turn = [&](vector<pii>& wood) {
    if(wood[0].first == wood[1].first) { // Horizontal
      wood[0].first = wood[1].first - 1;
      wood[0].second = wood[1].second;
      wood[2].first = wood[1].first + 1;
      wood[2].second = wood[1].second;
    } else { // Vertical
      wood[0].first = wood[1].first;
      wood[0].second = wood[1].second - 1;
      wood[2].first = wood[1].first;
      wood[2].second = wood[1].second + 1;
    }
  };
  auto checkCanDo = [&](vector<pii>& wood, bool isTurn) {
    auto checkBound = [&](pii& p) {
      if(p.first < 0 || p.second < 0 || p.first >= N || p.second >= N || board[p.first][p.second] == '1') return false;
      return true;
    };
    for(auto& b: wood) {
      if(checkBound(b) == false) return false;
    }
    int aroundPosX[8] = {-1, -1, -1, 0, 1, 1, 1, 0}; // Clockwise
    int aroundPosY[8] = {-1, 0, 1, 1, 1, 0, -1, -1}; // Clockwise
    if(isTurn) {
      auto& center = wood[1];
      for(int i = 0; i < 8; i++) {
        auto xToCheck = center.first + aroundPosX[i];
        auto yToCheck = center.second + aroundPosY[i];
        if(board[xToCheck][yToCheck] == '1') return false;
      }
    }
    return true;
  };

  function<void(vector<pii>&)> listOfDoing[5] = {moveRight, moveLeft, moveUp, moveDown, turn};
  map<vector<pii>, bool> checked;
  using pvi = pair<vector<pii>, int>;
  queue<pvi> q;
  q.push(pvi(wood, 0));
  checked[q.front().first] = true;

  int ans = INT32_MAX;
  while(q.empty() == false) {
    auto& curWood = q.front().first;
    D(
      cout << "Current wood: ";
      for(auto& b: wood) {
        cout << b.first << " " << b.second << " | ";
      }
      cout << endl;
    )
    auto& num = q.front().second;

    int idx = 0;
    for(auto f: listOfDoing) {
      auto newWood = curWood;
      f(newWood);
      sort(newWood.begin(), newWood.end());
      if(checkCanDo(newWood, idx == 4 ? true : false) && checked.find(newWood) == checked.end()) {
        D(cout << "Push to Queue" << endl;)
        D(
          for(auto& b: newWood) {
            cout << b.first << " " << b.second << " | ";
          }
          cout << endl;
        )
        q.push(pvi(newWood, num + 1));
        checked[newWood] = true;      
      }
      idx++;
    }

    auto checkDest = [&](const vector<pii>& wood) {
      for(int i = 0; i < wood.size(); i++) {
        if(wood[i] != dest[i]) return false;
      }
      return true;
    };

    if(checkDest(curWood)) {
      ans = min(ans, num);
    }

    q.pop();
  }

  cout << (ans == INT32_MAX ? 0 : ans) << endl;

  return 0;
}
