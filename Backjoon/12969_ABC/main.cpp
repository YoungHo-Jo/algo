#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <tuple>
#include <vector>

// Failed Code !!

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);

  int n, k;
  cin >> n >> k;

  using item = pair<tuple<int, int, int>, int>; // # of A B C, k num
  vector<map<string, item>> dp(n + 1);
  char chars[3] = {'A', 'B', 'C'};
  dp[1]["A"] = {{1, 0, 0}, 0};
  dp[1]["B"] = {{0, 1, 0}, 0};
  dp[1]["C"] = {{0, 0, 1}, 0};
  int maxK = 0;
  for(int i = 2; i < dp.size(); i++) {
    for(auto& e: dp[i - 1]) {
      auto& str = e.first;
      auto& nChar = e.second.first; 
      auto& kStr = e.second.second;
      maxK = max(maxK, kStr);
      if(kStr == k) {
        dp[i]['C' + str] = {nChar, k};
        break;
      }

      for(auto& c: chars) {
        auto newStr = c + str;
        auto newNChar = nChar;
        if(c == 'A') get<0>(newNChar)++;
        else if(c == 'B') get<1>(newNChar)++;
        else if(c == 'C') get<2>(newNChar)++;
        auto newK = kStr; 
        if(c == 'A') newK += get<1>(nChar) + get<2>(nChar);
        else if(c == 'B') newK += get<2>(nChar);
        if(newK <= k && maxK < newK) {
          dp[i][newStr] = {newNChar, newK};
        }
      }
    }
  }

  for(auto& d: dp) {
    cout << "====" << endl; 
    for(auto& e: d) {
      cout << e.first << " : " << e.second.second << endl;
    }
  }

  bool found = false;
  for(auto& e: dp[n]) {
    cout << e.first << " : " << e.second.second << endl;
    if(e.second.second == k) {
      cout << e.first << endl;
      found = true;

      cout << "Check: " << endl;
      int sum = 0;
      for(int i = 0; i < e.first.length(); i++) {
        for(int j = i + 1; j < e.first.length(); j++) {
          if(e.first[i] < e.first[j]) sum++; 
        }
      }
      break;
    }
  }
  if(found == false) cout << "-1" << endl;
  

  return 0;
}