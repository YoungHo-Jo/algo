#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstring>

using namespace std;

#ifdef DEBUG
#define D cout << __FUNCTION__ << ":" << __LINE__ << " >> "
#define massert(e) assert(e)
#else
#define D //D
#define massert(e) 
#endif

#define MAX 100
int tri[MAX][MAX];
int cache[MAX][MAX];
int n;

int solve(int row, int col) { 
  if(row >= n || col >= n) return 0;
  
  int& ret = cache[row][col];
  if(ret != -1) return ret;
  
//  ret = tri[row][col];
//  for(int j = col; j <= row; j++) {
//    ret = max(ret, solve(row + 1, col) + tri[row][col]);
//    ret = max(ret, solve(row + 1, col + 1) + tri[row][col]);
//  }

  return ret = max(solve(row + 1, col), solve(row + 1, col + 1)) +
    tri[row][col];
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C;
  cin >> C;
  for(int c = 0; c < C; c++) {
    int e;
    cin >> n;
    memset(cache, -1, sizeof(cache));

    for(int i = 0; i < n; i++) {
      for(int j = 0; j <= i; j++) {
        cin >> e;
        tri[i][j] = e;
      }
    }

    cout << solve(0, 0) << endl;
  }

  return 0;
}

