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

#define MAX 17 

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

  ui dp[MAX][MAX][2] = {0, };
  auto set = [&dp](const ui& i, const ui& j, ui first, ui second) {
    dp[i][j][0] = first;
    dp[i][j][1] = second;
  };
  for(ui i = 1; i <= N; i++) {
    for(ui j = 1; j <= N; j++) {
      if(i == 1 && j == 1 && N - j + 1 >= s[j].first) {
        D(cout << "Init" << endl;)
        set(i, j, s[1].first, s[1].second);
        continue;
      }

      auto comp = [](const ui* lhs, const ui* rhs) -> bool {
        return lhs[1] == rhs[1] ? lhs[0] > rhs[0] : lhs[1] < rhs[1];
      };

      if(i == j) {
        D(cout << "Find empty day" << endl;)
        ui* emptyDay = nullptr;
        for(ui k = 1; k < i; k++) {
          if(dp[k][j][0] == 0) {
            emptyDay = (emptyDay == nullptr) ? dp[k][j] : (emptyDay[1] < dp[k][j][1] ? dp[k][j] : emptyDay);
          }          
        }
        if(emptyDay != nullptr && N - j + 1 >= s[j].first) {
          D(cout << "There is an empty day " << endl;)
          set(i, j, s[j].first, (s[j].second + emptyDay[1]));
        } else if(N - j + 1>= s[j].first) {
          set(i, j,  s[j].first, s[j].second);
        }
      }

      auto upside = dp[i - 1][j];
      auto leftside = dp[i][j - 1];
      auto today = dp[i][j];
      auto maxPos = max(upside, max(leftside, today, comp), comp);

      if(maxPos == leftside) {
        D(cout << "Max post is left  at: " << i << " " << j << endl;)
        set(i, j, maxPos[0] == 0 ? 0 : maxPos[0] - 1, maxPos[1]);
      } else {
        set(i, j, maxPos[0], maxPos[1]);
      }
    }
  }  
  D(
    for(ui i = 1; i <= N; i++) {
      for(ui j = 1; j <= N; j++) {
        cout << dp[i][j][0] << " " << dp[i][j][1] << " | ";
      }
      cout << endl;
    }
  )

  cout << dp[N][N][1] << endl;



  return 0;
}