#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N, K;
  cin >> N >> K;
  const int MAX_ANGLE = 360; 
  bool dp[10][MAX_ANGLE] = {false, };
  vector<int> angles(N);
  for(int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    angles[i] = tmp;
  }


  for(int i = 0; i < N; i++) {
    auto check = [&](int& angle) {
      int multiplier= 1;
      while(angle*multiplier< 360) {
        dp[i][angle*multiplier] = true;
        multiplier++;
        if(angle == 0) break;
      }
    };
    if(i == 0) {
      dp[i][0] = true;
      check(angles[i]);
      continue;
    }
    check(angles[i]);
    for(int a = 0; a < MAX_ANGLE; a++) {
      if(dp[i - 1][a] == true) {
        int multiplier = 1;
        while(angles[i]*multiplier < 360) {
          // auto minusAngle = a - angles[i]*multiplier;
          // auto plusAngle = a + angles[i]*multiplier;
          // minusAngle += minusAngle < 0 ? 360 : 0;
          // plusAngle %= 360;
          auto minusAngle = abs(a - angles[i]*multiplier);
          auto plusAngle = a + angles[i]*multiplier;
          minusAngle %= 360;
          plusAngle %= 360;
          check(minusAngle);
          check(plusAngle);
          multiplier++;
        }
        check(a);
      }
    }
  }

  for(int i = 0; i < N; i++) {
    cout << i << ": =====" << endl;
    for(int j = 0; j < MAX_ANGLE; j++) {
      if(dp[i][j] == true) {
        cout << j << " "; 
      }
    }
    cout << endl;
  }
  while(K > 0) {
    int angle;
    cin >> angle;
    cout << (dp[N - 1][angle] ? "YES" : "NO") << endl;
    K--;
  }

  return 0;
}
