#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned int ui;

#define MAX 1001

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  ui N;
  cin >> N;
  
  ui nJump[MAX] = {0, };
  
  for(ui i = 1; i <= N; i++) {
    ui tmp;
    cin >> tmp; 
    nJump[i] = tmp;
  }

  ui dp[MAX][MAX] = {0, };

  for(ui i = 1; i <= N; i++) {
    for(ui j = i; j <= N; j++) {
      if(i == j) {
        dp[i][j] = dp[i - 1][j];
        D(cout << "i == j: " << dp[i][j] << endl;)
        if(i != 1 && dp[i][j] == 0) {
          D(cout << "can't go anymore" << endl;)
          break;
        }
        continue;
      }
      auto upside = dp[i - 1][j];
      auto leftside = dp[i][j - 1];
      leftside = (j - i <= nJump[i]) ? dp[i][i] + 1 : 0;
      auto minJump = min(leftside, upside);

      minJump = (minJump == 0) ? (leftside != 0 ? leftside : upside) : minJump;
      D(cout << "(" << i << ", " << j << ") " << minJump << endl;)
      dp[i][j] = minJump;
    }
  }

  D(
    for(ui i = 1; i <= N; i++) {
      for(ui j = 1; j <= N; j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }
  )

  if(N == 1) {
    cout << 0 << endl;
  } else if(dp[N][N] == 0) {
    cout << -1 << endl;
  } else {
    cout << dp[N][N] << endl;
  }



  


  return 0;
}