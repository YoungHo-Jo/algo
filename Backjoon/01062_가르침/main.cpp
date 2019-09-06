#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <bitset>

using namespace std;

typedef unsigned int ui;

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

int main(void) {
  string fixed = "antic";
  
  ui N, K;
  cin >> N >> K;
  vector<string> strs;
  string toLearn = "";
  if(K < 5) {
    cout << 0 << endl;
    return 0;
  } else {
    K -= 5;
  }
  
  for(ui i = 0; i < N; i++) {
    string str;
    cin >> str;
    if(str.size() < 8 || str.substr(0, 4).compare("anta") != 0 || str.substr(str.size() -4, 4).compare("tica") != 0) {
      continue;
    }

    size_t found = str.find_first_of(fixed);
    while(found != string::npos) {
      str.erase(found, 1);
      found = str.find_first_of(fixed);
    }
    strs.emplace_back(str);
    for(auto c: str) {
      size_t found = toLearn.find(c);
      if(found == string::npos) {
        toLearn.push_back(c);
      }
    }
  }
  D(cout << "to learn: " << toLearn << endl;)

  if(toLearn.size() <= K) {
    cout << strs.size() << endl;
    return 0;
  }

  ui maxNum = 0;
  vector<bool> mask(toLearn.size() - K, false);
  for(ui i = 0; i < K; i++) {
    mask.push_back(true);
  }

  do {
    string tmp;
    for(ui i = 0; i < mask.size(); i++) {
      if(mask[i] == true) {
        tmp.push_back(toLearn[i]);
      }
    }
    D(cout << "try: " << tmp << endl;)

    ui current = 0;
    for_each(strs.begin(), strs.end(), [&tmp, &current](const string& s) {
      string dummy = s;
      D(cout << dummy << endl;)
      auto found = s.find_first_of(tmp);
      while(found != string::npos) {
        dummy.erase(found, 1);
        found = dummy.find_first_of(tmp);
      }
      D(cout << "result: " << dummy << endl;)
      if(dummy.size() == 0) {
        current++;
        D(cout << "current: " << current << endl;)
      }
    });
    maxNum = max(current, maxNum);

  } while(next_permutation(mask.begin(), mask.end()));

  cout << maxNum << endl;


  return 0;
}