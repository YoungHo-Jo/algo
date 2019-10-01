#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

ostream& operator<<(ostream& os, const pair<int, int>& rhs) {
  os << rhs.first << " " << rhs.second;
  return os;
}

int main(void) {
  ios::sync_with_stdio(false);

  auto solve = [&]() {
    int N, W, H;
    cin >> N >> W >> H;

    vector<vector<int>> board(H, vector<int>(W, 0));
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) {
        int tmp;
        cin >> tmp;
        board[i][j] = tmp;
      }
    }
    using pii = pair<int, int>;
    auto checkBound = [&](const pii& pos) {
      return pos.first >= 0 && pos.first < H && pos.second >= 0 && pos.second < W;
    };
    const pii dOffset[4] = {
      {-1, 0}, {0, 1}, {1, 0}, {0, -1}
    };
    function<void(pii, int, int, vector<vector<int>>&)> erase = [&](pii from, int len, int direction, vector<vector<int>>& board) {
      D(cout << "Erase: " << from << " len: " << len << " direction: " << direction << endl;)
      if(len <= 0 || checkBound(from) == false) return;
      int prev = board[from.first][from.second];
      board[from.first][from.second] = 0;
      if(prev > 1) {
        D(cout << "Expand area to erase" << endl;) 
        for(int i = 0; i < 3; i++) erase(pii(from.first + dOffset[i].first, from.second + dOffset[i].second), prev - 1, i, board);
      } 
      erase(pii(from.first + dOffset[direction].first, from.second + dOffset[direction].second), len - 1, direction, board);
    };

    function<void(pii, pii, vector<vector<int>>&)> shrink = [&](pii to, pii which, vector<vector<int>>& board) {
      D(cout << "Shrink: " << to << " -> " << which << endl;)
      if(!checkBound(to) || !checkBound(which)) return;
      auto& toValue = board[to.first][to.second];
      auto& whichValue = board[which.first][which.second];

      if(toValue != 0 && whichValue != 0)  {
        D(cout << "both not zero" << endl);
        shrink(pii(to.first - 1, to.second), pii(which.first - 1, which.second), board);
      } else if(toValue == 0 && whichValue != 0) {
        D(cout << "which is zero" << endl;)
        swap(toValue, whichValue);
        shrink(pii(to.first - 1, to.second), pii(which.first - 1, which.second), board);
      } else if(toValue == 0 && whichValue == 0) 
        D(cout << "both zero" << endl;)
        shrink(to, pii(which.first - 1, which.second), board);
    };

    function<int(int idx, int num, vector<vector<int>>&)> breakBlocks = [&](int idx, int num, vector<vector<int>>& board) -> int {
      D(cout << "Breakblocks: " << idx << "  " << num << " " << endl;)
      D(
        cout << "Board: " << endl;
        for(auto& row: board) {
          for(auto& element: row) {
            cout << element << " ";
          }
          cout << endl;
        }
      )
      int sum = 0;
      if(num == 0) {
        for(auto& row: board) {
          for(auto& element: row) {
            if(element != 0) sum++;
          }
        }
        D(cout << "Reesult of Sum: " << sum << endl;)
        return sum;
      }
      if(idx >= W || idx < 0) return -1e9;

      // do with this idx
      for(int i = 0; i < H; i++) {
        if(board[i][idx] != 0) {
          auto boardCopied = board;
          erase(pii(i, idx), boardCopied[i][idx], 0, boardCopied);
          for(int j = 0; j < W; j++) {
            shrink(pii(N - 1, j), pii(N - 2, j), boardCopied);
          }
          sum = max({breakBlocks(idx, num - 1, boardCopied), breakBlocks(idx + 1, num - 1, boardCopied), breakBlocks(idx - 1, num - 1, boardCopied)});
          break;
        } 
      }

      // don't do with this idx
      return max({sum, breakBlocks(idx + 1, num, board), breakBlocks(idx - 1, num, board)});
    };

    // erase(pii(1, 0), 1, 0, board);

    cout << breakBlocks(0, N, board) << endl;;


  };

  solve();


  // int T;
  // cin >> T;


  return 0;
}