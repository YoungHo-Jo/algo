#include <iostream>
#include <vector>
#include <complex>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;

  vector<int> area(n, 0);
  
  for(int i = 0; i < n; i++) {
    int tmp;
    cin >> tmp;
    area[i] = tmp;
  }

  int master, slave;
  cin >> master >> slave;

  long long ans = n;
  while(true) {
    auto prev = ans;
    for(auto& a: area) {
      if(a - master > 0) {
        long long multiple = (a - master)/slave;
        if(multiple == 0) {
          a -= slave;
          ans++;
        } else {
          a -= multiple*slave;
          ans += multiple;
        }
      } 
    } 
    if(prev == ans) break;
  }
  
  
  cout << ans << endl;

  return 0;
}