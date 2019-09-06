#include <iostream>
#include <string>
#include <set>

using namespace std;
#define endl '\n'

int T;
string origin;

void solve(string& s, int idx, set<string>& cands) {
  if(s.size() == origin.size()) {
    cands.insert(string(s));
    return;
  }

  if(idx >= 1) {
    s.push_back(origin[idx - 1]);
    solve(s, idx + 1, cands);
    s.pop_back();
  }
  if(idx + 1 < origin.size()) {
    s.push_back(origin[idx + 1]);
    solve(s, idx + 1, cands);
    s.pop_back();
  }

  s.push_back(origin[idx]);
  solve(s, idx + 1, cands);
  s.pop_back();
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> T;
  for(int tc = 1; tc <= T; tc++) {
    cin >> origin;

    string s = "";
    set<string> cands;
    solve(s, 0, cands);
    cout << "#" << tc << " " << cands.size()%((int)(1e9 + 7)) << endl;
  }

  return 0;
}