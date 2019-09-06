#include <iostream>
#include <deque>
#include <utility>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functionalu

using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;


  auto solve = []() {
    int N, K;
    cin >> N >> K;
    deque<char> cap;
    for(int i = 0; i < N; i++) {
      char tmp;
      cin >> tmp;
      cap.push_back(tmp);
    }

    using mapPair = pair<string, bool>;
    auto comp = [](const mapPair& lhs, const mapPair& rhs) {
      return lhs.first > rhs.first;
    };

    vector<string> pwd;
    using pii = pair<int, int>;
    const int subStringPos[4] = {0, (N/4), (N/4)*2, (N/4)*3};
    for(int i = 0; i < N - 1; i++) { // N - 1 rotate
      for(auto& pos: subStringPos) {
        string str = "";
        for(int s = pos; s < pos + (N/4); s++) {
          str = str + cap[s];
        }
        pwd.push_back(str);
      }  
      char c = cap.back();
      cap.push_front(c);
      cap.pop_back();
    }  

    sort(pwd.begin(), pwd.end(), [](const string& lhs, const string& rhs) {
      return lhs > rhs;
    });

    string prev = "";
    int i = 0;
    for(auto& p: pwd) {
      if(p != prev) {
        prev = p;
        i++;
        if(i == K) {
          return (int)strtol(p.data(), NULL, 16);
          break;
        }
      }
    }  
  };
  

  for(int i = 1; i <= T; i++) {
    cout << "#" << i << " " << solve() << endl;
  }

  return 0;
}