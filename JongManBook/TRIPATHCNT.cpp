#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

int n;
int tri[100][100];
int cache[100][100];
int cntCache[100][100];

int solve(int row, int col) {
  if(row >= n || col >= n) return 0;
  
  int& ret = cache[row][col];
  if(ret != -1) return ret;
  ret = 0;
  return ret = max({
    ret, 
    solve(row + 1, col) + tri[row][col],
    solve(row + 1, col + 1) + tri[row][col],
  });
}

int count(int row, int col) {
  if(row >= n || col >= n) return 0;
  if(row == n - 1) return 1;

  int& ret = cntCache[row][col];
  if(ret != -1) return ret;

  ret = 0;
  if(solve(row + 1, col + 1) >= solve(row + 1, col)) 
    ret += count(row + 1, col + 1);
  if(solve(row + 1, col + 1) <= solve(row + 1, col)) 
    ret += count(row + 1, col);
  return ret;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  int C;
  cin >> C;
  for(int c = 0; c < C; c++) {
    cin >> n;
    int e;
    
    for(int i = 0; i < n; i++) {
      for(int j = 0; j <= i; j++) {
        cin >> e;
        tri[i][j] = e;
      }
    }

    memset(cache, -1, sizeof(cache));
    memset(cntCache, -1, sizeof(cntCache));
    
    solve(0, 0);
    cout << count(0, 0) << endl;
  }

  return 0;
}
