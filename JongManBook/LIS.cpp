#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#ifdef DEBUG
#define D cout << __FUNCTION__ << ":" << __LINE__ << " >> "
#define massert(e) assert(e)
#else
#define D //D
#define massert(e)
#endif

#define endl '\n'

int n;
int seq[500];

int cache[500];

int solve(int cur) {
  if(cur >= n) return 0; 
  
  int& ret = cache[cur];
  if(ret != -1) return ret;

  ret = 1;
  for(int i = cur + 1; i < n; i++) {
    if(seq[cur] < seq[i]) {
      ret = max(ret, solve(i) + 1);
    }
  }

  return ret;
}




int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C;
  cin >> C;
  for(int c = 0; c < C; c++) {
    int e;
    cin >> n;
    memset(cache, -1, sizeof(cache));
    for(int i = 0; i < n; i++) {
      cin >> e;
      seq[i] = e;
    }
    
    int ans = 1;
    for(int i = 0; i < n; i++) {
      ans = max(ans, solve(i));
    }
    
    cout << ans  << endl;
  }

  


  return 0;
}
