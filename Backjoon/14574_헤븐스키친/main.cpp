#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAX 1000

#define DBG
#ifdef DBG
#define D(x) x
#else
#define D(x)
#endif

typedef pair<int, int> pii;

int main(void) {
  ios::sync_with_stdio(false); cin.tie(0);
  int n;
  cin >> n;

  vector<pii> cooks(n);
  for(int i = 0; i < n; i++) {
    int p, c;
    cin >> p >> c;
    cooks[i] = pii(p, c);
  }

  int dp[MAX][MAX] = {0, };
  int maxWho[MAX] = {-1, };
  bool surviver[MAX] = {false, };
  for(int i = 0; i < n; i++) {
    surviver[i] = true;
    int max = 0;
    for(int j = i + 1; j < n; j++) {
      dp[i][j] = (cooks.at(i).second + cooks.at(j).second)/abs(cooks.at(i).first - cooks.at(j).first);
      dp[j][i] = dp[i][j];
    }
  }

  for(int i = 0; i < n; i++) {
    int maxValue = 0;
    for(int j = 0; j < n; j++) {
      if(i == j) continue;
      if(maxValue <= dp[i][j]) {
        maxWho[i] = j;
        maxValue = dp[i][j];
      } 
    }
  }

  D(
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        cout << dp[i][j] << " ";
      }
      cout << endl;
    }

  )

  int nContest = n - 1;
  int result = 0;
  vector<pii> match;
  while(nContest > 0) {
    D(
      cout << "Max who? " << endl;
      for(int i = 0; i < n; i++) {
        cout << maxWho[i] << " ";
      }
      cout << endl;

      cout << "Surviver: " << endl;
      for(int i = 0; i < n; i++) {
        cout << i << "(" << surviver[i] << ") ";
      }
      cout << endl;
    )

    int maxLhs = -1, maxRhs = -1;
    int maxTmp = 0;
    for(int i = 0; i < n; i++) {
      if(maxTmp <= dp[i][maxWho[i]] && surviver[maxWho[i]] && surviver[i]) {
        maxTmp = dp[i][maxWho[i]];
        maxLhs = i;
        maxRhs = maxWho[i];
      }
    }
    D(cout << "Max with: " << maxLhs << " " << maxRhs << endl;)
    result += maxTmp;    

    int maxAfterGoneOfLhs = 0;
    int maxAfterGoneOfRhs = 0;
    for(int i = 0; i < n; i++) {
      if(i != maxLhs && i != maxRhs) {
        if(maxWho[i] == maxLhs) {
          maxAfterGoneOfLhs = max(maxAfterGoneOfLhs, dp[i][maxLhs]);
        }
        if(maxWho[i] == maxRhs) {
          maxAfterGoneOfRhs = max(maxAfterGoneOfRhs, dp[i][maxRhs]);
        }
      }
    }
    
    D(cout << maxAfterGoneOfLhs << " vs. " << maxAfterGoneOfRhs << endl;)
    if(maxAfterGoneOfLhs >= maxAfterGoneOfRhs) {
      D(cout << "Lhs has more possiblity: bye! " << maxRhs << endl;)
      surviver[maxRhs] = false;
      maxWho[maxRhs] = -1;
      match.emplace_back(maxLhs, maxRhs);
    } else {
      D(cout << "Rhs has more possiblity: bye! " << maxLhs << endl;)
      surviver[maxLhs] = false;
      maxWho[maxLhs] = -1;
      match.emplace_back(maxRhs, maxLhs);
    }

    for(int i = 0; i < n; i++) {
      if(surviver[i]) {
        int maxValue = 0;
        for(int j = 0; j < n; j++) {
          if(maxValue <= dp[i][j] && surviver[j]) {
            maxValue = dp[i][j];
            maxWho[i] = j;
            D(cout << i <<  " -> " <<  j << " " << maxValue << endl;)
          }
        }
      }
    }

    nContest--;
  }

  cout << result << endl;
  for(auto& m: match) {
    cout << m.first + 1<< " " << m.second + 1<< endl;
  }




  return 0;
}