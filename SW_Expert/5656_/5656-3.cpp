#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

int n, w, h;
int board[15][12];

void print() {
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;
}



int getRemains() {
  int ret = 0;
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      if(board[i][j] != 0) {
        ret += 1;  
      }
    }
  }

  return ret;
}

void erase(const int& row, const int& col, vector<vector<bool>>& visited) {
  if(row < 0 || row >= h || col < 0 || col >= w) {
    return;
  }

  if(visited[row][col]) {
    return;
  }
  
  int nPropagation = board[row][col];
  board[row][col] = 0;  
  visited[row][col] = true;

  if(nPropagation == 1) {
    return;
  }
  
  for(int c = 1; c < nPropagation; c++) {
    int up = row - c;
    int down = row + c;
    int left = col - c;
    int right = col + c;
  
    erase(up, col, visited);
    erase(down, col, visited);
    erase(row, left, visited);
    erase(row, right, visited);
  }
}

void shrink() {


  for(int j = 0; j < w; j++) {
    int noZeroCnt = 0;
    for(int i = h - 1; i >= 0; i--) {
      if(board[i][j] >= 1) {
        int currentZeroIdx = h - 1 - noZeroCnt; 
        board[currentZeroIdx][j] = board[i][j];

        if(currentZeroIdx != i) {
          board[i][j] = 0;
        }

        noZeroCnt++;
      }
      
    }
  }

  /*
  for(int j = 0; j < w; j++) {
    while(true) {
      int i = h - 1;
      bool shrinked = true;
      while(i > 0) {
        if(board[i][j] == 0) {
          if(board[i - 1][j] != 0) shrinked = false;
          board[i][j] = board[i - 1][j];
          board[i - 1][j] = 0;
        }

        i--;
      }

      if(shrinked) break;
    }
  }
  */
}

int solve(int n) {
  if(n == 0) {
    return getRemains();
  }

  int ret = 1e9;
  for(int col = 0; col < w; col++) {
    int i = 0;
    // find not zero
    while(i < h && board[i][col] == 0) {
      i++;
    }
    if(i == h) continue;
    
    int temp[15][12];
    memcpy(temp, board, sizeof(board));
  
    vector<vector<bool>> visited(h, vector<bool>(w, false));
    erase(i, col, visited);
    shrink();

    ret = min(ret, solve(n - 1));     
    
    memcpy(board, temp, sizeof(board));
  }

  if(ret == 1e9) {
    return solve(0);
  }

  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int t = 1; t <= T; t++) {
    cin >> n >> w >> h;    
    int e;

    for(int i = 0; i < h; i++) {
      for(int j = 0; j < w; j++) {
        cin >> e;
        board[i][j] = e;
      }
    }
  
    cout << "#" << t << " " << solve(n) << endl;  
  }
  

  return 0;
}
