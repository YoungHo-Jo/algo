#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int ui;
typedef pair<ui, ui> pii;

// #define DEBUG
#ifdef DEBUG
#define D(X) X
#else
#define D(X) 
#endif

#define MAX 16 

int main(void) {

  ui N, T, P;
  cin >> N;

  vector<pii> s;
  s.push_back(pii(0, 0));
  for(ui i = 0; i < N; i++) {
    cin >> T >> P;
    D(cout << T << " : " << P << endl;)
    s.emplace_back(pii(T, P));
  }

  ui dp[MAX] = {0, };

  ui maxToday = 0;
  ui maxResult = 0;
  for(ui i = 1; i<= N; i++) {
    auto pos = s[i].first + i - 1;
    if(pos <= N) {
      dp[pos] = max(dp[pos], maxToday + s[i].second);
      maxResult = max(maxResult, dp[pos]);
    }
    maxToday = max(dp[i], maxToday);
  } 

  cout << maxResult << endl;



  return 0;
}