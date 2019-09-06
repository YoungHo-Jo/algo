#include <iostream>
#include <vector>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  vector<int> weight(n, 0);
  for(int i = 0; i < n; i++) {
    int tmp;
    cin >> tmp;
    weight[i] = tmp;
  }

  bool dp[2][30001] = {0, };
  const int OFFSET = 15000;
  for(int i = 0; i < weight.size(); i++) {
    if(i == 0)  {
      dp[i%2][OFFSET + weight[i]] = true;
      dp[i%2][OFFSET - weight[i]] = true;
      dp[i%2][OFFSET] = true;
    } else {
      for(int j = 0; j < 30001; j++) {
        if(dp[(i - 1)%2][j]) {
          dp[i%2][j + weight[i]] = true;
          dp[i%2][j - weight[i]] = true;
          dp[i%2][j] = true;
        }
        dp[(i - 1)%2][j] = false; // reset
      } 
    }
  }


  int nBall;
  cin >> nBall;
  while(nBall > 0) {
    int ball;
    cin >> ball;
    if(ball + OFFSET <= 30000 && dp[(n - 1)%2][ball + OFFSET] == true) cout << "Y ";
    else cout << "N ";
    nBall--;
  }

  

  return 0;
}