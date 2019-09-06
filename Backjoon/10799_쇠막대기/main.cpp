#include <iostream>
#include <stack>
#include <utility>
#include <string>

using namespace std;
#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

typedef unsigned int ui;
typedef pair<ui, ui> pii;

#define OPEN '('
#define CLOSE ')'

int main(void) {
  stack<pii> cuts;

  string inp;
  cin >> inp;
  ui level = 0;
  ui totalPipes = 0;
  for(auto i: inp) {
    level++;
    D(cout << i << " " << "level: " << level << endl;)
    if(i == CLOSE && level - cuts.top().first == 1 && cuts.top().second == 0) { // raser
      D(cout << "Razer" << endl;)
      cuts.pop();
      if(cuts.empty() == false) {
        cuts.top().second++;
        D(cout << "Cut: " << cuts.top().second << endl;)
        level = cuts.top().first;
        D(cout << "level to: " << level << endl;)
      } else {
        level = 0;
      }
    } else if(i == CLOSE) {
      auto top = cuts.top();
      totalPipes += cuts.top().second + 1;
      D(cout << "Current pipes: " << totalPipes << endl;)
      cuts.pop();
      if(cuts.empty() == false) {
        cuts.top().second += top.second;
      }
      level--;
    } else {
      cuts.push(pii(level, 0));
    }
  }

  cout << totalPipes << endl;

  return 0;
}

