#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define endl '\n'

bool p[10][10];
int nPapers[6] = {
  0, 5, 5, 5, 5, 5
};
int ans = 1e9;

bool check(const int& row, const int& col, const int& size) {
  for(int i = row; i < row + size; i++) {
    for(int j = col; j < col + size; j++) {
      if(p[i][j] == false) return false;
    }
  }
  return true;
}

void set(const int& row, const int& col, const int& size, bool value) {
  for(int i = row; i < row + size; i++) {
    for(int j = col; j < col + size; j++) {
      p[i][j] = value; 
    }
  }
}

int solve(const int& fromI, const int& fromJ, int used) {
  // find 1
  int row = -1, col = -1;
  for(int i = fromI; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      if(p[i][j] == true) {
        row = i;
        col = j;
        break;
      }
    }
    if(row != -1) break;
  }
  
  // all clear
  if(row == -1) {
    return ans = min(ans, used);
  }

  if(used >= ans) return ans;
  
  int ret = 1e9;
  for(int s = 1; s <= 5; s++) {
    if(nPapers[s] <= 0) continue;
    if(check(row, col, s)) {
      set(row, col, s, false);
      nPapers[s]--;

      ret = min(ret, solve(row, col + 1, used + 1));

      set(row, col, s, true);
      nPapers[s]++;
    }
  }

  return ret;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cout.tie(NULL);
  cin.tie(NULL);
  
  int inp;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      cin >> inp;
      p[i][j] = inp;
    }
  }

  int ans = solve(0, 0, 0);
  cout << (ans == 1e9 ? -1 : ans) << endl;

  return 0;
}
