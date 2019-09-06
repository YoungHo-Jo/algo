#include <iostream>
#include <vector>

using namespace std;


int main(void) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);
  vector<int> cache(1e6 + 1, 1);
  vector<long long> sumList(1e6 + 1, 0);
  for(int n = 1; n < 1e6 + 1; n++) {
    if(n >= 3 && n%2 == 1) {
      int mul = 1;
      int numCanMake = n*mul;
      while(numCanMake <= 1e6) {
        cache[numCanMake] += n;
        mul++;
        numCanMake = n*mul;
      }     
    }

    if(n == 1) {
      sumList[n] = 1;
    } else {
      sumList[n] = sumList[n - 1] + cache[n];
    }
  }

  int T;
  cin >> T;
  for(int t = 1; t <= T; t++) {
    int L, R;
    cin >> L >> R;
    long long ans = sumList[R] - sumList[L - 1];
    cout << "#" << t << " " << ans << endl;
  }  

  return 0;
}