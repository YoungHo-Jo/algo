#include <iostream>
#include <string>

using namespace std;

#define endl '\n'

int charToInt(char c) {
  return c - '0';
}

int solution(string s) {
  int answer = 0;

  for(int i = 0; i < s.size(); i++) {
    const char& c = s[i];
  
    if(c == '+' || c == '-') {
      continue;
    }

    answer = answer*10 + charToInt(c);
  }
  const char& first = s[0];
  if(first == '-') {
    answer *= -1;
  }

  return answer;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  return 0;
}