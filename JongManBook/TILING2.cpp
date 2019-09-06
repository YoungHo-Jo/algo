#include <iostream>
#include <cstring>

using namespace std;

#define endl '\n'

int cache[101];
const int MOD = 1000000007;
int solve(int n) {
  if(n <= 0) return 0;
  if(n <= 3) return n;

  int& ret = cache[n];
  if(ret != -1) return ret; 
  
  return ret = (solve(n - 1)%MOD + solve(n- 2)%MOD)%MOD;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C, n;
  cin >> C;
  memset(cache, -1, sizeof(cache));
  for(int c = 0; c < C; c++) {
    cin >> n;    
  
    cout << solve(n) << endl;
  }
  

  
  
  return 0;
}
