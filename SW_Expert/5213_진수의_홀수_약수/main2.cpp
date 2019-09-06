#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 1000001 
#define endl '\n'
long long cache[MAX] = {0, 1};

int main(void) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  for(int n = 2; n < MAX; n++) {
    cache[n] += 1;
    if(n >= 3 && n%2 == 1) {
      int numCanMake = n;
      while(numCanMake <= 1e6) {
        cache[numCanMake] += n;
        numCanMake += n;
      }     
    }

    cache[n] = cache[n - 1] + cache[n];
  }

  for(int t = 1; t <= T; t++) {
    int L, R;
    cin >> L >> R;
    cout << "#" << t << " " << cache[R] - cache[L - 1] << endl;
  }  

  return 0;
}

