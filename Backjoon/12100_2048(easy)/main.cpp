#include <iostream>
#include <vector>
#include <exception>
#include <stack>
#include <utility>
#include <functional>

using namespace std;

#define DBG
#ifdef DBG
#define D(x) x
#else
#define D(x)
#endif

enum Direction {
  Up = 1, Down, Left, Right
};


int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);

  int n;
  cin >> n;

  vector<vector<int>> b(n, vector<int>(n, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      int tmp;
      cin >> tmp;
      b[i][j] = tmp;
   }
  }

  auto move = [&](vector<vector<int>>& board, Direction d) {
    auto check = [&](int i, int j) {
      // according to Direction, if Blocks can be come together
      try {
        switch(d) {
          case Up:
            for(int k = i + 1; k < board.size(); k++) {
              if(board.at(k).at(j) != 0) {
                return board.at(i).at(j) == board.at(k).at(j);
              }
            }
            break;
          case Down:
            for(int k = i - 1; k >= 0; k--) {
              if(board.at(k).at(j) != 0) {
                return board.at(i).at(j) == board.at(k).at(j);
              }
            }
            break;
          case Left:
            for(int k = j + 1; k < board.size(); k++) {
              if(board.at(i).at(k) != 0) {
                return board.at(i).at(j) == board.at(i).at(k);
              }
            }
            break;
          case Right:
            for(int k = j - 1; k >= 0; k--) {
              if(board.at(i).at(k) != 0) {
                return board.at(i).at(j) == board.at(i).at(k);
              }
            }
            break;
        }
      } catch(exception e) {
        return false;
      }
      return false;
    };

    auto shrink = [&](int i, int j) {
      int value = 0;
      switch(d) {
        case Up:
          for(int k = i; k < board.size() - 1; k++) {
            value = max(board[k][j], value);
            value = max(board[k + 1][j], value);
            swap(board[k][j], board[k + 1][j]);
          }
          break;
        case Down:
          for(int k = i; k > 0; k--) {
            value = max(board[k][j], value);
            value = max(board[k - 1][j], value);
            swap(board[k][j], board[k - 1][j]);
          }
          break;
        case Left: 
          for(int k = j; k < board.size() - 1; k++) {
            value = max(board[i][k], value);
            value = max(board[i][k + 1], value);
            swap(board[i][k], board[i][k + 1]);
          }
          break;
        case Right:
          for(int k = j; k > 0; k--) {
            value = max(board[i][k], value);
            value = max(board[i][k - 1], value);
            swap(board[i][k], board[i][k - 1]);
          }
          break;
      }
      return value != 0;
    };
    
    auto combine = [&](int i, int j) {
      if(!check(i, j)) return 0;
      return board.at(i).at(j)*2;
    };

    auto goLoop = [&](function<void(const int& i, const int& j)> callback) {
      switch(d) {
        case Up:
          for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board.size(); j++) {
              callback(i, j);
            }
          }
          break;
        case Down:
          for(int i = board.size() - 1; i >= 0; i--) {
            for(int j = 0; j < board.size(); j++) {
              callback(i, j);
            }
          }
          break;
        case Right:
          for(int i = 0; i < board.size(); i++) {
            for(int j = board.size() - 1; j >= 0; j--) {
              callback(i, j);
            }
          }
          break;
        case Left:
          for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board.size(); j++) {
              callback(i, j);
            }
          }
          break;
      }
    };

    int maxValue = 0;

    goLoop([&](const int& i, const int& j) {
      if(board[i][j] == 0) {
        bool isNotAllZero = shrink(i, j);
        while(board[i][j] == 0 && isNotAllZero) {
          isNotAllZero = shrink(i, j); 
        }
      }
      auto combinedValue = combine(i, j);
      if(combinedValue != 0) {
        board[i][j] = 0;
        bool isNotAllZero = shrink(i, j);
        while(board[i][j] == 0 && isNotAllZero) {
          isNotAllZero = shrink(i, j); 
        }
        board[i][j] = combinedValue;
      } 
      maxValue = max(maxValue, board[i][j]);

    });

    D(
      for(auto& row: board) {
        for(auto& e: row) {
          cout << e << " ";
        }
        cout << endl;
      }
    )

    return maxValue;
  };

  function<int(vector<vector<int>>, Direction, int)> dfs = [&](vector<vector<int>> board, Direction d, int depth) {
    int maxValue = 0;
    if(depth != 0) {
      D(cout << "Depth: " << depth << " d: " << d << endl;)
      maxValue = move(board, d);
    }
    if(depth == 5) {
      return maxValue;
    }


    maxValue = max(maxValue, dfs(board, Up, depth + 1));
    maxValue = max(maxValue, dfs(board, Right, depth + 1));
    maxValue = max(maxValue, dfs(board, Down, depth + 1));
    maxValue = max(maxValue, dfs(board, Left, depth + 1));
    return maxValue;
  };

  cout << dfs(b, Up, 0) << endl;

  return 0;
}
