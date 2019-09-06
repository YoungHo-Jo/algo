#include <iostream>
#include <utility>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
typedef pair<int, string> pis;

int main(void) {
  int L, C;
  cin >> L >> C;
  string cnd;

  for(int i = 0; i < C; i++) {
    char inp;
    cin >> inp;
    cnd.push_back(inp);
  }

  auto addStr = [&](string& str, int pos) -> bool {
    if(str.size() == L) return false;
    str.push_back(cnd[pos]);
    return true;
  };

  auto checkVowel = [](string& str) -> bool {
    string vowel = "aeiou";
    return str.find_first_of(vowel) != string::npos;
  };

  auto checkConsonant = [](string& str) -> bool {
    string consonant = "bcdfghjklmnpqrstvwxyz";
    auto found = str.find_first_of(consonant);
    if(found != string::npos) {
      found = str.find_first_of(consonant, found + 1);
      if(found != string::npos) {
        return true;
      }
      return false;
    }
    return false;
  };

  stack<pis> s;
  for(int i = 0; i < C; i++) {
    string newStr = "";
    addStr(newStr, i);
    s.push(pis(i, newStr));
  }

  vector<string> result;
  while(s.empty() == false) {
    auto top = s.top();
    auto curPos = top.first;
    auto str = top.second;
    s.pop();
    if(checkVowel(str) && checkConsonant(str) && str.size() == L) {
      sort(str.begin(), str.end());
      result.emplace_back(str);
      continue;
    }
    
    for(int i = curPos + 1; i < C; i++) {
      auto newStr = str;
      if(addStr(newStr, i)) {
        s.push(pis(i, newStr)); 
      }
    }
  }

  sort(result.begin(), result.end());
  for(auto& s: result) {
    cout << s << endl;
  }

  return 0;
}