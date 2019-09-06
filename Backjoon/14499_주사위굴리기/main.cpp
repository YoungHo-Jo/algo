#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false);

  int N, M, x, y, K;
  cin >> N >> M >> x >> y >> K;
  
  vector<vector<int>> map(N, vector<int>(M, 0));
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      int tmp;
      cin >> tmp;
      map[i][j] = tmp;
    }
  }  

  using pii = pair<int, int>;

  vector<vector<int>> dice(4, vector<int>(3, 0));
  
  auto moveUp = [&]() {
    auto tmp = dice[0][1];
    for(int i = 0; i < 3; i++) { 
      dice[i][1] = dice[i + 1][1];
    }
    dice[3][1] = tmp;
  };

  auto moveDown = [&]() {
    auto tmp = dice[3][1];
    for(int i = 3; i > 0; i--) {
      dice[i][1] = dice[i - 1][1];
    }
    dice[0][1] = tmp;
  };

  std::map<pii, pii> mapping;
  mapping[pii(0, 1)] = pii(0, 1);
  mapping[pii(1, 0)] = pii(1, 1);
  mapping[pii(1, 1)] = pii(1, 2);
  mapping[pii(1, 2)] = pii(3, 1);
  mapping[pii(2, 1)] = pii(2, 1);
  mapping[pii(3, 1)] = pii(1, 0);

  auto moveRight = [&]() {
    auto newDice = dice;
    for(auto& m: mapping) {
      auto& which = m.first;
      auto& where = m.second;
      newDice[where.first][where.second] = dice[which.first][which.second];
    }
    dice = newDice;
  };

  auto moveLeft = [&]() {
    auto newDice = dice;
    for(auto& m: mapping) {
      auto& which = m.second;
      auto& where = m.first;
      newDice[where.first][where.second] = dice[which.first][which.second];
    }
    dice = newDice;
  };

  int dx[5] = {0, 0, 0, -1, 1};
  int dy[5] = {0, 1, -1, 0, 0};
  function<void()> listOfDoing[5] = {0, moveRight, moveLeft, moveUp, moveDown};


  while(K > 0) {
    int cmd;
    cin >> cmd;

    auto checkToGo = [&](int command) {
      int newX = x + dx[command];
      int newY = y + dy[command];
      if(newX < 0 || newX >= N || newY < 0 || newY >= M) return false;
      return true; 
    };
    
    if(checkToGo(cmd)) {
      D(cout << "cmd: " << cmd << endl;)
      listOfDoing[cmd]();
      x += dx[cmd];
      y += dy[cmd];
      if(map[x][y] == 0) {
        map[x][y] = dice[3][1];
      } else {
        dice[3][1] = map[x][y];
        map[x][y] = 0;
      }
      cout << dice[1][1] << endl;
    }
    K--;

    D(
      cout << "Current dice: " << endl;
      for(auto& row: dice) {
        for(auto& d: row) {
          cout << d << " ";
        }
        cout << endl;
      }
    )

    D(
      cout << "Current map: " << endl;
      for(auto& row: map) {
        for(auto& m: row) {
          cout << m << " ";
        }
        cout << endl;
      }
      cout << endl;
    )
  }
   
 
  return 0;
}