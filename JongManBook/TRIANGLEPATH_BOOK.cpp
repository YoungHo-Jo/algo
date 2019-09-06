#include <iostream>
#include <cstring>

using namespace std;

int n, triangle[100][100];
int cache2[100][100];

int path2(int y, int x) {
  // base
  if( y == n - 1) return triangle[y][x];

  // memoization
  int& ret = cache2[y][x];
  if(ret != -1) return ret;
  return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + 
    triangle[y][x];
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
    memset(cache2, -1, sizeof(cache2));
    for(int i = 0; i < n; i++) {
      for(int j = 0; j <= i; j++) {
        cin >> e;
        triangle[i][j] = e;
      }
    }

    cout << path2(0, 0) << endl;
  }

  

  return 0;
}

