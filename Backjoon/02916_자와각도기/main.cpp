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
    auto check = [&](const int& angle) {
      int multiplier = 1;
      while(angle*multiplier < 360) {
        int tmp = angle*multiplier;
        dp[i%2][tmp] = true; 
        multiplier++;
        if(tmp == 0) break;
      };
    };
    if(i == 0) {
      dp[i][angles[i]] = true;
      check(angles[i]);
      continue;
    } 
    for(int a = 0; a < MAX_ANGLE; a++) {
      if(dp[(i - 1)%2][a] == true) {
        auto minusAngle = abs(a - angles[i]);
        auto plusAngle = a + angles[i];
        minusAngle %= 360;
        plusAngle %= 360;
        check(a);
        check(minusAngle);
        check(plusAngle);
        dp[(i - 1)%2][a] = false;
      }
    }
  }

  while(K > 0) {
    int a;
    cin >> a;
    cout << (dp[(N - 1)%2][a] ? "YES" : "NO") << endl;
    K--;
  }

  return 0;
}
