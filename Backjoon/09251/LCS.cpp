#include <iostream>
#include <cstring>


using namespace std;

#define MAX 1001

int main(void) {

  int dp[MAX][MAX];
  memset(dp, 0, sizeof(dp));

  string s1, s2;

  cin >> s1 >> s2;

  for(int i = 1; i <= s1.size(); i++) {
    for(int j = 1; j <= s2.size(); j++) {
      int case1 = (s1[i - 1] == s2[j - 1]) ?
        dp[i - 1][j - 1] + 1 :
        dp[i - 1][j - 1];
      int case2 = max(dp[i - 1][j], dp[i][j - 1]);
      dp[i][j] = max(case1, case2);
    } 
  }


  cout << dp[s1.size()][s2.size()] << endl;


  return 0;
}