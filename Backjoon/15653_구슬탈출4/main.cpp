#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <utility>

using namespace std;

using pii = pair<int, int>;
using piipii = pair<pii, pii>;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

enum Direction {
  up = 1, down, left, right
};

int main(void) {
  ios::sync_with_stdio(false);
  int N, M;

  cin >> N >> M;


  vector<vector<char>> board(N, vector<char>(M, '.'));
  piipii stones(pii(0, 0), pii(0, 0));
  pii hole(0, 0);
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      char tmp;
      cin >> tmp;
      if(tmp == 'R') stones.first = pii(i, j);
      else if(tmp == 'B') stones.second = pii(i, j);
      else {
        if(tmp == 'O') hole = pii(i, j);
        board[i][j] = tmp;
      }
    }
  }
  D(
    cout << endl;
    for(auto& row: board) {
      for(auto& e: row) {
        cout << e;
      }
      cout << endl;
    }
    cout << endl;
  )
  
  auto getMovedPos = [&](const pii& cur, const Direction direction) {
    auto& x = cur.first;
    auto& y = cur.second;
    pii result = cur;
    switch(direction) {
      case Direction::up:
        for(int i = cur.first - 1; i >= 1; i--) {
          if(board[i][y] == '#') break;
          result.first--;
          if(board[i][y] == 'O') break;
        }
      break;
      case Direction::down:
        for(int i = cur.first + 1; i < N - 1; i++) {
          if(board[i][y] == '#') break;
          result.first++;
          if(board[i][y] == 'O') break;
        }
      break;
      case Direction::left:
        for(int j = cur.second - 1; j >= 1; j--) {
          if(board[x][j] == '#') break;
          result.second--;
          if(board[x][j] == 'O') break;
        }
      break;
      case Direction::right:
        for(int j = cur.second + 1; j < M - 1; j++) {
          if(board[x][j] == '#') break;
          result.second++;
          if(board[x][j] == 'O') break;
        }
      break;
    }
    return result;
  };

  using node = pair<piipii, int>;

  queue<node> bfs;
  map<piipii, bool> checked;
  bfs.push(node(stones, 0));
  int ans = INT32_MAX; 
  while(bfs.empty() == false) {
    auto& cur = bfs.front().first;
    auto& depth = bfs.front().second;
    auto& red = cur.first;
    auto& blue = cur.second;
    D(cout << "Current Node: " << red.first << " " << red.second << " | " << blue.first << " " << blue.second << endl;)
    D(cout << "Depth: " << depth << endl;)

    D(
      cout << endl;
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
          if(red.first == i && red.second == j) cout << "R";
          else if(blue.first == i && blue.second == j) cout << "B";
          else cout << board[i][j];
        }
        cout << endl;
      }
      cout << endl;
    )

    auto moveBoth = [&](piipii cur, const Direction d) {
      auto result = cur;
      result.first = getMovedPos(result.first, d);
      result.second = getMovedPos(result.second, d);
      if(result.first == result.second && result.first != hole) {

        auto& nearToLeftUpCorner = (cur.first.first < cur.second.first) ? result.first 
         : ((cur.first.second < cur.second.second) ? result.first : result.second);
        auto& nearToRightDownCorner = (cur.first.first > cur.second.first) ? result.first 
         : ((cur.first.second > cur.second.second) ? result.first : result.second);
        D(cout << "Before Calibration: " << result.first.first << " " << result.first.second << " | " << result.second.first << " " << result.second.second << endl;)
        switch(d) {
          case Direction::up:
            nearToRightDownCorner.first++;
          break;
          case Direction::down:
            nearToLeftUpCorner.first--;
          break;
          case Direction::left:
            nearToRightDownCorner.second++;
          break;
          case Direction::right:
            nearToLeftUpCorner.second--;
          break;
        }
        D(cout << "After Calibration: " << result.first.first << " " << result.first.second << " | " << result.second.first << " " << result.second.second << endl;)
      }
      return result;
    };

    auto movedUp = moveBoth(cur, Direction::up);
    auto movedDown = moveBoth(cur, Direction::down);
    auto movedLeft = moveBoth(cur, Direction::left);
    auto movedRight = moveBoth(cur, Direction::right);

    auto pushToQ = [&](const piipii& moved) {
      if(moved != cur && checked.find(moved) == checked.end() && moved.second != hole) {
        bfs.push(node(moved, depth + 1));
        checked[moved] = true;
        D(cout << "Pushed to Queue" << endl;)
        D(cout << "=> Node: " << moved.first.first << " " << moved.first.second << " | " << moved.second.first << " " << moved.second.second << endl;)
      }
    };

    pushToQ(movedUp);
    pushToQ(movedDown);
    pushToQ(movedLeft);
    pushToQ(movedRight);

    if(red == hole && blue != hole) {
      ans = min(ans, depth);
      break;
    } 
    bfs.pop();
  }

  cout << (ans == INT32_MAX ? -1 : ans) << endl;
  

    
  return 0;
}