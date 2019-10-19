#include <iostream>
#include <complex>
#include <map>
#include <utility>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

// #define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  auto solve = [&]() {

    using pii = pair<int, int>;
    int N;
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N, 0));
    map<int, vector<pii>> wormholes;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        int tmp;
        cin >> tmp;
        board[i][j] = tmp;
        if(tmp >= 6) {
          wormholes[tmp].push_back(pii(i, j));
        }
      }
    }
    const pii dOffset[4] = {
      {-1, 0}, {0, 1}, {1, 0}, {0, -1} // 0: up 1: right 2: down 3: left
    };
    auto checkBound = [&](const pii& pos) {
      return !(pos.first < 0 || pos.first >= N || pos.second < 0 || pos.second >= N);
    };
    auto getNextPos = [&](const pii& current, const int& state) {
      return pii(current.first + dOffset[state].first, current.second + dOffset[state].second);
    };
    auto getNextState = [&](const pii& current, const int& state) {
      auto nextPos = getNextPos(current, state);
      auto block = 0;
      if(!checkBound(nextPos)) {
        block = 5;
      } else {
        block = board[nextPos.first][nextPos.second];
      }

      const int stateMapOnBlock[4][6] =  {
        {0, 2, 1, 3, 2, 2},
        {0, 3, 3, 2, 0, 3},
        {0, 1, 0, 0, 3, 0},
        {0, 0, 2, 1, 1, 1},
      };
      if(0 < block && block <= 5) {
        return stateMapOnBlock[state][block];
      } else if(block == 0) {
        return state; 
      } else {
        return -1;
      }
    };

    using piii = pair<pii, int>;  
    function<piii(const pii&, const int&)> getRealNextPos = [&](const pii& current, const int& state) -> piii {
      auto nextState = getNextState(current, state);
      piii result;
      auto nextPos = getNextPos(current, state);
      if(nextState == -1) { // worm hole or black hole
        if(board[nextPos.first][nextPos.second] == -1) result = piii(pii(-1, -1), -1); 
        else {
          auto posOfholes = wormholes[board[nextPos.first][nextPos.second]];
          for(auto& pos: posOfholes) {
            if(pos != nextPos) {
              nextPos = pos;
              break;
            }
          }
          // nextPos = getNextPos(nextPos, state);
          result = piii(nextPos, state);
          // result = getRealNextPos(nextPos, state);
        }
      } else if(state != nextState) { // 90 angle or bounce
        // nextPos = getNextPos(nextPos, nextState);
        result = piii(nextPos, nextState);
        // result = getRealNextPos(nextPos, nextState);
      } else {
        result = piii(nextPos, state);
      }
      // if(!checkBound(result.first)) result = piii(pii(-1, -1), -1);
      return result;
    };

    // pii test1 = pii(6, 18);
    // auto result = getNextPos(test1, 3);
    // cout << result.first << " " << result.second << " " << endl;
    // cout << checkBound(result) << endl;
    // cout << getNextState(test1, 3) << endl;
    // auto result2 = getRealNextPos(test1, 3);
    // cout << result2.first.first << " " << result2.first.second << " " << result2.second << endl;

    // return 0;

    // Not good
    int ans = 0;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        D(cout << "Current: " << i << " " << j << endl;)
        auto& block = board[i][j];
        if(block == 0) {
          auto startPos = pii(i, j);
          for(int s = 0; s < 4; s++) {
            piii ball = getRealNextPos(startPos, s);
            int sum = 0;
            auto prevState = s;
            while(ball.first != startPos) { 
              D(cout << "Ball: " << ball.first.first << " " << ball.first.second << " s: " << ball.second << " StartPos: " << startPos.first << 
              " " << startPos.second << " " << s << endl;)
              if(ball.second == -1) break;
              else if(prevState != ball.second) {
                sum++;
                prevState = ball.second;
              }
              // D(cout << "block: " << board[ball.first.first][ball.first.second] << endl;)
              ball = getRealNextPos(ball.first, ball.second);
            }  
            ans = max(ans, sum);
          }
        }
      }
    }
    return ans;
  };

  for(int i = 1; i <= T; i++) {
    cout << "#" << i << " " << solve() << endl;
  }
  return 0;
}