#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>



using namespace std;

#define endl '\n'


string inp;
int cache[10000];


int getLevel(const string& str) {
  if(str.size() == 0) return 0;

  char prev = str[0];
  
  // 1
  for(int i = 1; i < str.size(); i++) {
    if(prev == str[i]) {
      if(i == str.size() - 1) return 1;
      continue;
    } else break;
  }
  
  // 2 5
  int diff = 10;
  for(int i = 1; i < str.size(); i++) {
    if(diff == 10) diff = prev - str[i];
    else if(diff != prev - str[i]) break;
    else if(diff == prev - str[i]) {
      if(i == str.size() - 1) {
        return diff == 1 || diff == -1 ? 2 : 5;
      }
    } 

    prev = str[i];
  }
  
  // 4
  prev = str[0];
  diff = 10;
  for(int i = 1; i < str.size(); i++) {
    if(diff == 10) diff = prev - str[i];
    else if(prev - str[i] == -diff) {
      if(i == str.size() - 1) {
        return 4;
      }
      diff *= -1;
    } else {
      break;
    }
    
    prev = str[i]; 
  }

  return 10;
}

int solve(int idx) {
  if(idx > inp.size()) return 1e9;
  if(idx == inp.size()) return 0;
  
  int& ret = cache[idx];
  if(ret != -1) return ret;
  ret = 1e9;
  for(int i = 3; i <= 5; i++) {
    if(idx + i > inp.size()) continue;
        
    string str = inp.substr(idx, i);
    int level = getLevel(str);

    ret = min(ret, solve(idx + i) + getLevel(str)); 
  } 

  return ret;
}

const int INF = 987654321;
int classify(int a, int b) {
  string str = inp.substr(a, b - a + 1);
  // 1
  if(str == string(str.size(), str[0])) return 1;
  
  // 4
  bool progressive = true;
  for(int i = 0; i < str.size() - 1; i++) {
    if(str[i + 1] - str[i] != str[1] - str[0]) {
      progressive = false;
    }
  }

  if(progressive && abs(str[1] - str[0]) == 1) 
    return 2;

  bool alternating = true;
  for(int i = 0; i < str.size(); i++) {
    if(str[i] != str[i % 2]) {
      alternating = false;
    }
  }
  
  if(alternating) return 4;
  if(progressive) return 5;
  return 10;
}

int cache2[10002];
int memorize(int begin) {
  if(begin == inp.size()) return 0;
  int& ret = cache2[begin];
  if(ret != -1) return ret;

  ret = INF;
  for(int L = 3; L <= 5; L++) {
    if(begin + L <= inp.size()) {
      ret = min(ret, memorize(begin + L) + 
        classify(begin, begin + L - 1));
    }
  }

  return ret;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int C;
  cin >> C;
  for(int c = 0; c < C; c++) {
    cin >> inp;
  
    memset(cache, -1, sizeof(cache));
    cout << solve(0) << endl; 

   // memset(cache2, -1, sizeof(cache2));
   // cout << memorize(0) << endl; 
  }



  return 0;
}
