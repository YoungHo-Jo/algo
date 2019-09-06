#include <iostream>
#include <string>

using namespace std;
#define endl '\n'

int T;
string origin;
#define MOD ((int)(1e9 + 7))

long solve() {
  long ret = 1;
  for(int i = 0; i < origin.size(); i++) {
    if(i == 0) {
      if(origin[i] != origin[i + 1]) {
        ret *= 2;
        ret %= MOD; 
      }
    } else if(i == origin.size() - 1) {
      if(origin[i] != origin[i - 1]) {
        ret *= 2;
        ret %= MOD; 
      }
    } else {
      char left = origin[i - 1], mid = origin[i], right = origin[i + 1];
      if(left != mid && mid != right && left != right) {
        ret *= 3;
        ret %= MOD;
      } else if(!(left == mid && mid == right)) {
        ret *= 2;
        ret %= MOD;
      }
    }
  }

  return ret%MOD;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> T;
  for(int tc = 1; tc <= T; tc++) {
    cin >> origin;

    cout << "#" << tc << " " << solve() << endl;
  }

  return 0;
}