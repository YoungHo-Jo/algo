#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

vector<int> h;

int solve(int left, int right) {
  D(cout << "--------" << endl;)
  D(cout << "left: " << left << " right: " << right << endl;)

  // base case
  if(left == right) {
    D(cout << "---End---( left: " << left << " right: " << right << ")" << endl;)
    return h[left];
  }
  
  int mid = (left + right)/2;
  int ret = max(solve(left, mid), solve(mid + 1, right));

  int lo = mid, hi = mid + 1;
  int height = min(h[lo], h[hi]);
  ret = max(ret, height * 2);
  D(cout << "Start with lo: " << lo << " hi: " << hi << endl;)
  while(left < lo || hi < right) {
    if(hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
      hi++;
      height = min(height, h[hi]);
    } else {
      lo--;
      height = min(height, h[lo]);
    }

    D(cout << "move to lo: " << lo << " hi: " << hi << endl;)
    ret = max(ret , height * (hi - lo + 1));
    D(cout << "The maximum size is Currently: " << ret << endl;)
  }

  D(cout << "---End---( left: " << left << " right: " << right << ")" << endl;)
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  for(int t = 0; t < T; t++) {
    int n, temp;
    cin >> n;
    h.clear();
    for(int i = 0; i < n; i++) {
      cin >> temp;
      h.push_back(temp);
    }
    
    cout << solve(0, n - 1) << endl;
  }

  return 0;
}