#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <tuple>
#include <vector>
#include <functional>

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n, k;
  cin >> n >> k;

  using item = pair<tuple<int, int, int>, int>; // # of A B C, k num

  char chars[3] = {'A', 'B', 'C'};

  map<item, bool> checked;
  string str(n, ' ');
  function<bool(int, item&)> solve = [&](int idx, item& e) {
    if(idx >= n) {
      if(e.second == k) return true;
      return false;
    } 
    // cout << str << endl;

    auto makeItem = [&](char c) {
      item newItem = e;
      auto& nChar = newItem.first;
      if(c == 'A') get<0>(nChar)++;
      else if(c == 'B') get<1>(nChar)++;
      else if(c == 'C') get<2>(nChar)++;
      auto& newK = newItem.second; 
      if(c == 'A') newK += get<1>(e.first) + get<2>(e.first);
      else if(c == 'B') newK += get<2>(e.first);
      return newItem;
    };

    bool result = false;
    for(auto c: chars) {
      auto newItem = makeItem(c);
      str[n - idx - 1] = c;
      if(checked.find(newItem) == checked.end()) {
        checked[newItem] = true;
        if(solve(idx + 1, newItem)) return true;
      }
      else str[n - idx - 1] = ' ';
    }
    return false; // unable to make string with k
  };

  item e = {{0, 0, 0}, 0};
  if(solve(0, e)) cout << str << endl;
  else cout << "-1" << endl;

  return 0;
}