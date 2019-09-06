#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define endl '\n'

int N, K;
int w[100];
int v[100];

int cache[100][100000];

int solve(int idx, int k) {
  if(idx >= N) return 0;
  
  int &ret = cache[idx][k];
  if(ret != -1) return ret; 

  ret = solve(idx + 1, k);
  if(k - w[idx] >= 0) ret = max(ret, solve(idx + 1, k - w[idx]) + v[idx]);
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N >> K;
  memset(cache, -1, sizeof(cache));
  
  int win, vin;
  for(int i = 0; i < N; i++) {
    cin >> win >> vin;
    w[i] = win;
    v[i] = vin;
  }

  cout << solve(0, K) << endl;
    

}
