#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>


using namespace std;

#define endl '\n'

int N, M;
double cache[1000][1000];


double solve(int n, int m) {
  if(n >= N && m <= M) return 1;
  if(m > M) return 0;
  double& ret = cache[n][m];
  if(ret >= 0) return ret;

  return ret = (double)solve(n + 1, m + 1)*0.25 + (double)solve(n + 2, m + 1)*0.75;
}



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C;
  cin >> C;

  
  for(int c = 0; c < C; c++) {
    cin >> N >> M; 
    
    for(int i = 0; i < 1000; i++) {
      for(int j = 0; j < 1000; j++) {
        cache[i][j] = -1.0;
      }
    }
    
    cout << solve(0, 0) << endl;

  }

  return 0;
}
