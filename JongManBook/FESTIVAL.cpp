#include <iostream>
#include <algorithm>

using namespace std;

#define endl '\n'

int N, L;
int cost[1000];
int cCost[1000];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int tc = 0; tc < T; tc++) {
    cin >> N >> L;

    int temp;
    for(int i = 0; i < N; i++) {
      cin >> temp;
      cost[i] = temp;
    }

    cCost[0] = cost[0];
    for(int i = 1; i < N; i++) {
      cCost[i] = cCost[i - 1] + cost[i];
    }
  
    double result = 1e9;
    for(int i = 0; i <= N - L; i++) {
      for(int j = i + L - 1; j < N; j++) {
        result = min(result, ((double)(cCost[j] - cCost[i] + cost[i]))/(j - i + 1));
      }
    }
    cout << fixed;    
    cout.precision(11);
    cout << result << endl;
  }

  return 0;
}
