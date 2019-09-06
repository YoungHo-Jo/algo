#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int N, K;
  cin >> N >> K;
  const int MAX_ANGLE = 360; 
  vector<int> angles(N);
  for(int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    angles[i] = tmp;
  }

  bool dp[10][MAX_ANGLE] = {false, };
  bool possibleAngles[MAX_ANGLE] = {false, };
  function<void(int, int)> solve = [&](int idx, int angle) {
    if(idx >= N) return;
    if(dp[idx][angle] == true) return;
    dp[idx][angle] = true;
    possibleAngles[angle] = true;
    auto plusAngle = (angle + angles[idx]) % 360;
    if(dp[idx][plusAngle] == false) solve(idx, plusAngle);
    auto minusAngle = (angle - angles[idx]);
    minusAngle += minusAngle < 0 ? 360 : 0;
    if(dp[idx][minusAngle] == false) solve(idx, minusAngle);
    solve(idx + 1, angle);
  };

  solve(0, 0);
  for(int i = 0; i < N; i++) {
    cout << i << ": =====" << endl;
    for(int j = 0; j < MAX_ANGLE; j++) {
      if(dp[i][j] == true) cout << j << " ";
    }
    cout << endl;
  }

  while(K > 0) {
    int angle;
    cin >> angle;
    cout << (possibleAngles[angle] ? "YES" : "NO") << endl;
    K--;
  }

  return 0;
}
