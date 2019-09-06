#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <list>
using namespace std;

#define endl '\n'

int T;

int getSecs(string str) {
  stringstream ss(str);
  int ret = 0;
  for(int i = 2; i >= 0; i--) {
    string token;
    getline(ss, token, ':');
    ret += stoi(token)*pow(60, i);
  }
  return ret;
}

string getStrTime(int secs) {
  list<string> ll;

  while(secs > 0) {
    string s = to_string(secs%60);
    if(s.size() == 0) s = "00";
    if(s.size() == 1) s = "0" + s;
    ll.push_front(s);
    secs /= 60;
  }

  while(ll.size() < 3) {
    ll.push_front("00");
  }

  string ret = "";
  for(list<string>::iterator it = ll.begin(); it != ll.end(); it++) {
    ret = ret + *it;
    if(next(it) != ll.end()) {
      ret = ret + ":";
    }
  }
  return ret;
}

string solve(string lhs, string rhs) {
  int lhsSecs = getSecs(lhs);
  int rhsSecs = getSecs(rhs);
  if(lhsSecs > rhsSecs) rhsSecs += 24*60*60;

  return getStrTime(rhsSecs - lhsSecs);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);


  cin >> T;
  for(int tc = 1; tc <= T; tc++) {
    string lhs, rhs;
    cin >> lhs >> rhs;

    cout << "#" << tc << " " << solve(lhs, rhs) << endl;
  }


}