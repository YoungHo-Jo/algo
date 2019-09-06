#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cassert>

using namespace std;

#ifdef DEBUG
#define D cout << " [DEBUG] " << __FUNCTION__ << ":" << __LINE__ << " >> " 
#define DBG(x) x
#define asrt(e) assert(e)
#else
#define D //D
#define asrt(e) 
#define DBG(x) 
#endif

#define endl '\n'

vector<vector<int>> opers({
  {0, 1, 2},
  {3, 7, 9, 11},
  {4, 10, 14, 15},
  {0, 4, 5, 6, 7},
  {6, 7, 8, 10, 12},
  {0, 2, 14, 15},
  {3, 14, 15},
  {4, 5, 7, 14, 15},
  {1, 2, 3, 4, 5},
  {3, 4, 5, 9, 13}
});

bool check(const vector<int>& clocks) {
  for(int i = 0; i < clocks.size(); i++) {
    if(clocks[i] != 12) return false;
  }
  return true;
}

void set(vector<int>& clocks, const int whichSwitch, int delta) {
  const vector<int>& to = opers[whichSwitch];

  for(int i = 0; i < to.size(); i++) {
    clocks[to[i]] += (3 * delta);
    if(clocks[to[i]] > 12) clocks[to[i]] %= 12;
    asrt(clocks[to[i]] <= 12);
    asrt(clocks[to[i]] != 0);
  }
}

int solve(vector<int>& clocks, int whichSwitch, int nTotal) {
  if(whichSwitch > 9) {
    return check(clocks) ? nTotal : 1e9;
  }

  int ret = 1e9;  
  ret = min(ret, solve(clocks, whichSwitch + 1, nTotal));
  for(int i = 1; i < 4; i++) {
    set(clocks, whichSwitch, i);
    DBG(
      D << "Current clcoks: ";
      for(int i = 0; i < clocks.size(); i++) {
        cout << clocks[i] << " ";
      }
      cout << endl;
    )
    ret = min(ret, solve(clocks, whichSwitch + 1, nTotal + i));
    set(clocks, whichSwitch, 4 - i);
  }

  return ret;
}



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int nTest;
  cin >> nTest;
  for(int t = 0; t < nTest; t++) {
    vector<int> clocks;
    int c;
    for(int i = 0; i < 16; i++) {
      cin >> c; 
      clocks.push_back(c);
    }
  
    int result = solve(clocks, 0, 0);
    result = result == 1e9 ? -1 : result;
    cout << result << endl;
    
  }


  return 0;
}
