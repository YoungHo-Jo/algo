#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define endl '\n'

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif
int n, w, h, e;
int board[15][12];
int temp[15][12];

void set(const int& i, const int& j, const int& delta, vector<vector<bool>>& visited) {
  // base case
  D(
    cout << __FUNCTION__ << ": i=" << i << " j=" << j << " delta=" << delta << endl;
  )
  if(i < 0 || i >= h || j < 0 || j >= w) return;
  if(visited[i][j]) return;

  if(board[i][j] != 0)
    temp[i][j] = delta;
  visited[i][j] = true;
  
  for(int c = 1; c <= board[i][j]; c++) {
    int up = i - c;
    int down = i + c;
    int left = j - c;
    int right = j + c;
    
    set(up, j, delta, visited); 
    set(down, j, delta, visited);
    set(i, left, delta, visited);
    set(i, right, delta, visited);
  }
}

void shrink() {
  for(int j = 0; j < w; j++) {
    int i = h - 1;
    while(i > 0) {
      if(board[i][j] == 0) {
        // swap
        board[i][j] = board[i - 1][j];  
      }

      i--;
    }
  }
}


int solve(const int& n) {
  D(
    cout << __FUNCTION__ << ": n=" << n << endl;
  )
  // base case
  if(n <= 0) {
    D(
      cout << "Base case" << endl;
    )
    int ans = 0; 
    for(int i = 0; i < h; i++) {
      for(int j = 0; j < w; j++) {
        D(
          cout << temp[i][j] << " ";
        )
        ans += temp[i][j] == 1 ? 1 : 0; 
      }
      D(
        cout << endl;
      )
    }
    
    D(
      cout << "ans: " << ans << endl << endl;
    )

    return ans;
  }
  
  int ret = 1e9;
  for(int col = 0; col < w; col++) {
    // erase
    int i = 0;
    while(i < h && temp[i][col] == 0) i++;
    if(i == h) continue;
  
    D(
      cout << "erase i=" << i << " col: " << col << endl;
    )
    vector<vector<bool>> visited(h, vector<bool>(w, false));
    set(i, col, 0, visited);
    shrink();
    
    D(
      cout << "after erase temp: " << endl;
      for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
          cout << temp[y][x] << " ";
        }
        cout << endl;
      }
      cout << endl;
    )

    ret = min(ret, solve(n - 1));

    D(
      cout << "recover i=" << i << " col: " << col << endl;
    )
    visited.assign(h, vector<bool>(w, false));
    set(i, col, 1, visited);

    D(
      cout << "after recover temp: " << endl;
      for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
          cout << temp[y][x] << " ";
        }
        cout << endl;
      }
      cout << endl;
    )
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
    
    for(int i = 0; i < h; i++) {
      for(int j = 0; j < w; j++) {
        cin >> e;
        board[i][j] = e;
        temp[i][j] = e != 0 ? 1 : 0;
      }
    }

    cout << "#" << t << " " << solve(n) << endl;
  }


  return 0;
}
