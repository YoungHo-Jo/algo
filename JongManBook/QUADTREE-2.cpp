#include <iostream>
#include <string>
#include <iterator>

using namespace std;

#define endl '\n'

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

string inp;

string solve(string::iterator& it) {
  char head = *it;

  it++;
  
  if(head == 'b' || head == 'w') {
    return string(1, head);
  }

  string upperLeft = solve(it);
  string upperRight = solve(it);
  string lowerLeft = solve(it);
  string lowerRight = solve(it);

  return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  int t;
  cin >> t;
  while(t--) {
    cin >> inp;
  
    string::iterator it = inp.begin();
    cout << solve(it) << endl;
  }


  return 0;
}
