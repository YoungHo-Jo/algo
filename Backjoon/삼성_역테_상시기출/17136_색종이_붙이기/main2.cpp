#include <iostream>
#include <cstring>

using namespace std;

#define endl '\n'

bool p[10][10];
int maxSize[10][10];
bool pStatus[10][10];
bool allClear = false;
int nOnes = 0;

void set(const int& row, const int& col, const int& size, bool value) {
  if(row >= 10 || col >= 10) return; 
  if(size <= 0) return;

  pStatus[row][col] = value;
  set(row, col + 1, size - 1, value);
  set(row + 1, col + 1, size - 1, value);
  set(row + 1, col, size - 1, value);
}

int getMaxSize(int row, int col) {
  int& ret = maxSize[row][col];
  if(ret != -1) return ret;
  if(p[row][col] == false) return ret = 0;

  ret = 1;
  for(int s = 2; s <= 5; s++) {
    bool succeed = true;
    row++;
    col++;
    for(int d = 1; d < s; d++) {
      int i = row - d;
      int j = col - d;
      if(i < 0 || j < 0) succeed = false;
      if(p[row][j] == false || p[i][col] == false) succeed = false;
    }

    if(succeed == true) {
      ret = max(ret, s);
    } else break;

  }
  return ret;
}

bool check(const int& row, const int& col, const int& size) {
  for(int i = row; i < row + size; i++) {
    for(int j = col; j < col + size; j++) {
      if(pStatus[i][j] == false) return false;
    }
  }
  return true;
}

void print(bool arr[10][10]) {
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;
}

int solve(int usedPaper[6], const int& used) {
  if(used > 25) return 1e9;

  int ret = 1e9;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      int size = getMaxSize(i, j);
      for(int s = 1; s <= size; s++) {
        if(usedPaper[s] < 5 && check(i, j, s)) {
          cout << "Before: " << endl;
          print(pStatus);
          set(i, j, size, false);
          nOnes -= size*size;
          usedPaper[s]++;

          cout << "After: " << endl;
          print(pStatus);

          ret = min(ret, solve(usedPaper, used + 1));
          usedPaper[s]--;
          nOnes += size*size;
          set(i, j, size, true);
        } else if(usedPaper[s] == 5) {
          return 1e9; 
        }
      }
    }
  }


  return nOnes == 0 ? used : ret;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  // get paper
  int inp;
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      cin >> inp;
      p[i][j] = inp;
      pStatus[i][j] = inp;
      nOnes += inp;
    }
  }
  
  int usedPaper[6] = {
    0, 0, 0, 0, 0, 0
  };

  memset(maxSize, -1, sizeof(maxSize));
  
  int ans = solve(usedPaper, 0);
  if(ans == 1e9) ans = -1;
  cout << ans << endl;

  return 0;
}
